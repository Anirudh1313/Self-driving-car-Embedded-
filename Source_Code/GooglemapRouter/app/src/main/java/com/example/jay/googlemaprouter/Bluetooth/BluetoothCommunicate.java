package com.example.jay.googlemaprouter.Bluetooth;

import android.bluetooth.BluetoothSocket;
import android.graphics.Color;
import android.util.Log;

import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * Created by jay on 10/22/2017.
 */

public class BluetoothCommunicate{
        private final BluetoothSocket mmSocket;
        private  InputStream mmInStream;
        private  OutputStream mmOutStream;
        byte[] buffer = new byte[12];

        public BluetoothCommunicate(BluetoothSocket socket) {
            mmSocket = socket;
        }

    public void read() {
        LatLng currentPos = new LatLng(0.00,0.00);
        Log.i("Bluetooth","Start Reading");
                try {

                    InputStream inputStream = mmSocket.getInputStream();
                    String in_str;
                    do
                    {
                        inputStream.read(buffer,0,1);
                        in_str = new String(buffer);
                       // Log.i("Bluetooth","received data : waiting For @ "+in_str.substring(0,1));
                    }while(!in_str.substring(0,1).equals("#"));

                    /*inputStream.read(buffer,0,11);
                    in_str = new String(buffer);
                    Log.i("Bluetooth","received data : Latitude "+in_str);*/
                     in_str = "";
                    String str;
                    do {

                        inputStream.read(buffer,0,1);
                         str = new String(buffer);
                        in_str= in_str.concat(str.substring(0,1));
                       // Log.i("Bluetooth","received data : waiting For # "+str.substring(0,1));
                    }while(!str.substring(0,1).equals("@"));

                    Log.i("Bluetooth","received data : Latitude "+in_str.substring(0,in_str.length()-1));

                    in_str = "";
                    do {

                        inputStream.read(buffer,0,1);
                        str = new String(buffer);
                        in_str = in_str.concat(str.substring(0,1));
                        //Log.i("Bluetooth","received data : waiting For new line "+str.substring(0,1));
                    }while(!str.substring(0,1).equals("\n"));

                    Log.i("Bluetooth","received data : Longitude "+in_str.substring(0,in_str.length()-1));
                } catch (IOException e) {
                    Log.i("Bluetooth", "Exception received data : " + e);
                }
                return;
    }

  /*  public LatLng putBuffer(byte[] buffer)
    {

        String str[] = new String(buffer).split("#");
        LatLng currentPos = new LatLng(0.00,0.00);
        Log.i("Bluetooth","received data : ");
        for(int i=0;i<str.length;i++)
        {
            if(!str[i].isEmpty())
            {
                String recData[] = str[i].split("@");
                Log.i("Bluetooth","received data : Latitude value is "+recData[0]+"Longitude value is "+recData[1]);
               // LatLng currentPos = new LatLng(Double.parseDouble(recData[0]),Double.parseDouble(recData[1]));

            }
        }
        return currentPos;

    }*/

    public void write(byte[] bytes) {
        try {
            mmOutStream = mmSocket.getOutputStream();
            mmOutStream.write(bytes);
            Log.i("Bluetooth","Transmitted ");
        } catch (IOException e) {
            Log.i("Bluetooth","Exception Write data : "+e);
        }
    }
    public void cancel() {
        try {
            mmSocket.close();
        } catch (IOException e) { }
    }

}
