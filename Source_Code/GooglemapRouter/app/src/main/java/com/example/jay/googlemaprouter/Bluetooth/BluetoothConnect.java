package com.example.jay.googlemaprouter.Bluetooth;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.IOException;
import java.util.UUID;

public class BluetoothConnect extends Thread{
    private final BluetoothSocket mmSocket;
    private final BluetoothDevice mmDevice;
    BluetoothAdapter mBluetoothAdapter;
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");

    public BluetoothConnect(BluetoothDevice device,BluetoothAdapter mBluetoothAdapter) {
        this.mBluetoothAdapter = mBluetoothAdapter;
        BluetoothSocket tmp = null;
        mmDevice = device;
        try {
            tmp =(BluetoothSocket) device.getClass().getMethod("createRfcommSocket", new Class[] {int.class}).invoke(device,1);
           // tmp = device.createRfcommSocketToServiceRecord(MY_UUID);
        } catch (Exception e) {
            Log.i("Bluetooth","Error in create Socket " + e.toString() );

        }
        mmSocket = tmp;
        try {
            mmSocket.connect();
            Log.i("BLE_Connect","mmSocket is : "+mmSocket.toString());

        } catch (IOException connectException) {
            Log.i("Bluetooth","Error in connecting Socket " + connectException );
            try {
                mmSocket.close();
            } catch (IOException closeException) {
                Log.i("BLE_Connect","BLE_connect Exception"+closeException);
            }

        }
          /*  try {
                mmSocket.close();
            } catch (IOException closeException) {
            }
            */

        return;
    }
    public void run() {
       // mBluetoothAdapter.cancelDiscovery();
        try {
               mmSocket.connect();
               Log.i("BLE_Reconnect","Connected");

        } catch (IOException connectException) {
            try {
                Log.i("BLE_Connect","BLE_connect Exception"+connectException);
                mmSocket.close();
            } catch (IOException closeException) {
                Log.i("BLE_Connect","BLE_connect Exception"+closeException);
            }

        }
    }

    public BluetoothSocket get_socket()
    {
        return mmSocket;
    }


    public void cancel() {
        try {
            mmSocket.close();
        } catch (IOException e) { }
    }
}