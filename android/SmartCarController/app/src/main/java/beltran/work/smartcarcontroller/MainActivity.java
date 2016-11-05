package beltran.work.smartcarcontroller;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.CompoundButton;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.io.IOException;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

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

    ToggleButton toggleButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
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
        new ConnectThread(device).start();
        toggleButton = (ToggleButton) findViewById(R.id.toggleButton);
        toggleButton.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                sendData(isChecked ? 'A' : 'B');
            }
        });
    }

    private void sendData(char data) {
        if (outStream == null) {
            Toast.makeText(MainActivity.this, "No Out Stream :-(", Toast.LENGTH_SHORT).show();
            Log.e(TAG, "No Out Stream");
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
            }
            socket = tmp;
        }

        public void run() {
            if (socket == null) {
                Log.e(TAG, "Socket null, nothing to do");
                return;
            }
            try {
                // Connect the device through the socket. This will block
                // until it succeeds or throws an exception
                socket.connect();
            } catch (IOException connectException) {
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
                Log.e(TAG, e.getMessage(), e);
            }
            Log.d(TAG, "Out Stream ready!");
        }

        public void cancel() {
            try {
                if (socket != null) {
                    socket.close();
                }
            } catch (IOException e) {
                Log.e(TAG, e.getMessage(), e);
            }
        }
    }
}
