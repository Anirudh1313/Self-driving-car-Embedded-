package com.example.jay.googlemaprouter.Bluetooth;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.util.Log;

import java.io.IOException;
import java.util.UUID;

/**
 * Created by jay on 10/22/2017.
 */


public class BluetoothConnect extends Thread {
    private BluetoothSocket bTSocket;

    public boolean connect(BluetoothDevice bTDevice, UUID mUUID) {
        // BluetoothSocket temp = null;
        try {
            bTSocket = bTDevice.createRfcommSocketToServiceRecord(mUUID);
        } catch (IOException e) {
            Log.d("CONNECTTHREAD", "Could not create RFCOMM socket:" + e.toString());
            return false;
        }
        try {
            bTSocket.connect();
        } catch (IOException e) {
            Log.d("CONNECTTHREAD", "Could not connect: " + e.toString());
            return false;}
           /* try {
                bTSocket.close();
            } catch (IOException close) {
                Log.d("CONNECTTHREAD", "Could not close connection:" + close.toString());
                return false;
            }*/

        return true;
    }

    public boolean cancel() {
        try {
            bTSocket.close();
        } catch (IOException e) {
            Log.d("CONNECTTHREAD", "Could not close connection:" + e.toString());
            return false;
        }
        return true;

    }


}

     class AcceptThread extends Thread {
        private final BluetoothServerSocket mmServerSocket;
        UUID MY_UUID = 	UUID.fromString("00001105-0000-1000-8000-00805f9b34fb");
        public AcceptThread(BluetoothAdapter mBluetoothAdapter) {
            // Use a temporary object that is later assigned to mmServerSocket
            // because mmServerSocket is final.
            BluetoothServerSocket tmp = null;
            try {
                // MY_UUID is the app's UUID string, also used by the client code.
                tmp = mBluetoothAdapter.listenUsingRfcommWithServiceRecord("googlemaprouter", MY_UUID);
            } catch (IOException e) {
                Log.e("Tag", "Socket's listen() method failed", e);
            }
            mmServerSocket = tmp;
        }

        public void run() {
            BluetoothSocket socket = null;
            // Keep listening until exception occurs or a socket is returned.
            while (true) {
                try {
                    socket = mmServerSocket.accept();
                } catch (IOException e) {
                    Log.e("Tag", "Socket's accept() method failed", e);
                    break;
                }

                if (socket != null) {
                    // A connection was accepted. Perform work associated with
                    // the connection in a separate thread.
                    //manageMyConnectedSocket(socket);
                    try {
                        mmServerSocket.close();
                        break;
                    } catch (IOException e) {
                        Log.e("Tag", "Socket's close() method failed", e);
                        break;
                    }


                }
            }
        }

        // Closes the connect socket and causes the thread to finish.
        public void cancel() {
            try {
                mmServerSocket.close();
            } catch (IOException e) {
                Log.e("TAG", "Could not close the connect socket", e);
            }
        }
    }




