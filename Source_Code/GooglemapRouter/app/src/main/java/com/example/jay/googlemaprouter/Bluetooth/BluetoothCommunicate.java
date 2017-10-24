package com.example.jay.googlemaprouter.Bluetooth;

import android.bluetooth.BluetoothSocket;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * Created by jay on 10/22/2017.
 */

public class BluetoothCommunicate {

    public void sendData(BluetoothSocket bTSocket,int data) throws IOException {
        ByteArrayOutputStream output = new ByteArrayOutputStream(4);
        output.write(data);
        OutputStream outputStream = bTSocket.getOutputStream();
        outputStream.write(output.toByteArray());
    }

    public int receiveData(BluetoothSocket bTSocket) throws IOException{
        byte[] buffer = new byte[4];
        ByteArrayInputStream input = new ByteArrayInputStream(buffer);
        InputStream inputStream = bTSocket.getInputStream();
        inputStream.read(buffer);
        return input.read();
    }

}
