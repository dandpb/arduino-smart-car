package beltran.work.smartcarcontroller;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

import butterknife.BindDrawable;
import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class MainActivity extends AppCompatActivity {
    private static final int REQUEST_ENABLE_BT = 1;
    private static final String TAG = "MainActivity";
    private static final String HC_06 = "HC-06";
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Nullable
    private BluetoothAdapter bluetoothAdapter;
    @Nullable
    private BluetoothDevice device;
    @Nullable
    private OutputStream outStream;

    @BindView(R.id.toggleButton)
    ToggleButton toggleButton;
    @BindView(R.id.button_connect)
    Button buttonConnect;
    @BindDrawable(R.drawable.ic_bluetooth_searching_black_24dp)
    Drawable icConnecting;
    @BindDrawable(R.drawable.ic_bluetooth_disabled_black_24dp)
    Drawable icDisconnected;
    @BindDrawable(R.drawable.ic_bluetooth_black_24dp)
    Drawable icBluetooth;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);
        disconnected();
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (bluetoothAdapter == null) {
            // Device does not support Bluetooth
            Toast.makeText(this, "No Bluetooth", Toast.LENGTH_SHORT).show();
            Log.e(TAG, "No Bluetooth :-(");
            return;
        }
        if (!bluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
            return;
        }
        Set<BluetoothDevice> pairedDevices = bluetoothAdapter.getBondedDevices();
        if (pairedDevices.size() > 0) {
            for (BluetoothDevice device : pairedDevices) {
                Log.d(TAG, device.getName() + "\n" + device.getAddress());
                if (device.getName().equals(HC_06)) {
                    this.device = device;
                }
            }
        }
        if (device == null) {
            Toast.makeText(this, "Device Not Found :-(", Toast.LENGTH_SHORT).show();
            Log.e(TAG, "Device Not Found :-(");
            return;
        }
        toggleButton.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                sendData(isChecked ? 'A' : 'B');
            }
        });
        connect();
    }

    @OnClick(R.id.buttonUp)
    public void onClickUp() {
        sendData('U');
    }

    @OnClick(R.id.buttonDown)
    public void onClickDown() {
        sendData('D');
    }

    @OnClick(R.id.buttonLeft)
    public void onClickLeft() {
        sendData('L');
    }

    @OnClick(R.id.buttonRight)
    public void onClickRight() {
        sendData('R');
    }

    private void sendData(char data) {
        if (outStream == null) {
            Toast.makeText(MainActivity.this, "No Out Stream :-(", Toast.LENGTH_SHORT).show();
            Log.e(TAG, "No Out Stream");
            return;
        }
        byte[] msgBuffer = new byte[1];
        msgBuffer[0] = (byte) data;
        Log.d(TAG, "...Send data: " + data + "...");
        try {
            outStream.write(msgBuffer);
        } catch (IOException e) {
            Log.e(TAG, e.getMessage(), e);
        }
    }

    private class ConnectThread extends Thread {
        @Nullable
        private final BluetoothSocket socket;

        ConnectThread(@NonNull BluetoothDevice device) {
            BluetoothSocket tmp = null;
            try {
                tmp = device.createRfcommSocketToServiceRecord(MY_UUID);
            } catch (IOException e) {
                Log.e(TAG, e.getMessage(), e);
                disconnected();
            }
            socket = tmp;
        }

        public void run() {
            if (socket == null) {
                Log.e(TAG, "Socket null, nothing to do");
                disconnected();
                return;
            }
            try {
                // Connect the device through the socket. This will block
                // until it succeeds or throws an exception
                socket.connect();
            } catch (IOException connectException) {
                disconnected();
                // Unable to connect; close the socket and get out
                try {
                    socket.close();
                } catch (IOException closeException) {
                    Log.e(TAG, closeException.getMessage(), closeException);
                }
                return;
            }
            try {
                outStream = socket.getOutputStream();
            } catch (IOException e) {
                disconnected();
                Log.e(TAG, e.getMessage(), e);
            }
            Log.d(TAG, "Out Stream ready!");
            connected();
        }
    }

    private void disconnected() {
        runOnUiThread(new Runnable() {
            public void run() {
                buttonConnect.setCompoundDrawablesWithIntrinsicBounds(icDisconnected, null, null, null);
                buttonConnect.setText(R.string.disconnected);
            }
        });
    }

    private void connected() {
        runOnUiThread(new Runnable() {
            public void run() {
                buttonConnect.setCompoundDrawablesWithIntrinsicBounds(icBluetooth, null, null, null);
                buttonConnect.setText(R.string.connected);
            }
        });
    }

    @OnClick(R.id.button_connect)
    public void onClickButtonConnect() {
        connect();
    }

    private void connect() {
        if (device != null) {
            buttonConnect.setCompoundDrawablesWithIntrinsicBounds(icConnecting, null, null, null);
            buttonConnect.setText(R.string.connecting);
            new ConnectThread(device).start();
        }
    }
}
