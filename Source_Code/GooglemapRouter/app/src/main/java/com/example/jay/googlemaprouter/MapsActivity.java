package com.example.jay.googlemaprouter;

import com.example.jay.googlemaprouter.Bluetooth.*;


import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.graphics.Color;
import android.os.ParcelUuid;
import android.os.Parcelable;
import android.support.v4.app.FragmentActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import com.example.jay.googlemaprouter.Map.MapCommands;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import java.util.ArrayList;
import java.util.Set;
import java.util.UUID;


public class MapsActivity extends FragmentActivity implements OnMapReadyCallback,
        GoogleMap.OnMapClickListener{

    private GoogleMap mMap;
    ArrayList<BluetoothAdapter> array_adapter;
    ArrayList<BluetoothDevice> ble_devices;
    BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);

    }


    /**
     * Manipulates the map once available.
     * This callback is triggered when the map is ready to be used.
     * This is where we can add markers or lines, add listeners or move the camera. In this case,
     * we just add a marker near Sydney, Australia.
     * If Google Play services is not installed on the device, the user will be prompted to install
     * it inside the SupportMapFragment. This method will only be triggered once the user has
     * installed Google Play services and returned to the app.
     */
    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;

        // Add a marker in Sydney and move the camera
       LatLng SJSU = new LatLng(37.3361179, -121.8817006);
        //Drawable circleDrawable = getResources().getDrawable(R.drawable);
       // BitmapDescriptor markerIcon = getMarkerIconFromDrawable(circleDrawable);
        mMap.addCircle(new CircleOptions()
                .strokeWidth(4)
                .radius(4)
                .center(SJSU)
                .strokeColor(Color.parseColor("#B20000"))
                .fillColor(Color.parseColor("#FF1919")));
        mMap.addMarker(new MarkerOptions().position(SJSU).title("Marker in SJSU").icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_BLUE)));
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(SJSU,18));
       // mMap.moveCamera(CameraUpdateFactory.newLatLng(SJSU));
        initListeners();
    }


    // Setting onclick event listener for the map
    @Override
    public void onMapClick(LatLng latLng) {
        mMap.clear();
        LatLng SJSU = new LatLng(37.3361179, -121.8817006);
        mMap.addCircle(new CircleOptions()
                .strokeWidth(4)
                .radius(4)
                .center(SJSU)
                .strokeColor(Color.parseColor("#B20000"))
                .fillColor(Color.parseColor("#FF1919")));
        mMap.addMarker(new MarkerOptions().position(SJSU).title("Marker in SJSU").icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_BLUE)));

        //Toast.makeText(MapsActivity.this, "Latitude is: "+latLng.latitude+", Longtitude is: "+latLng.longitude, Toast.LENGTH_LONG).show();
        mMap.addMarker(new MarkerOptions().position(latLng).title("Destination"));
        mMap.moveCamera(CameraUpdateFactory.newLatLngZoom(latLng,18));

        ArrayList points = new ArrayList();
        points.add(SJSU);
        points.add(latLng);

        MapCommands mapCommands = new MapCommands();
        mapCommands.drowline(points,mMap);

        connect_alpha();
    }


    /*
    This function will add listener
     */
    private void initListeners() {
        mMap.setOnMapClickListener(this);
    }



    private void connect_alpha() {
        BluetoothConnection bluetooth_conn = new BluetoothConnection(MapsActivity.this);
        bluetooth_conn.bluethoot_enable();
        UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");
        //discover_device();
        Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
        for (BluetoothDevice device : pairedDevices) {
            Toast.makeText(MapsActivity.this, "Got Alpha " + device.getName(), Toast.LENGTH_LONG).show();
           // Log.i("Alpha", "paired Device : " + device.getName());
            if (device.getName().equals("HC-05")) {
                Log.i("Alpha", "got Alpha");
                Toast.makeText(MapsActivity.this, "Got Alpha ", Toast.LENGTH_LONG).show();
                BluetoothConnect bt_Thread = new BluetoothConnect();

                Parcelable[] uuidExtra = (ParcelUuid[]) device.getUuids();

               /* for (Parcelable Dev_uuid : uuidExtra) {
                    Log.i("UUID : ", Dev_uuid.toString());
                }*/
                boolean conn = bt_Thread.connect(device, MY_UUID);
                Log.w("Blutooth connection ","Bluetooth connection status : "+conn);
               /* try{
                    bt_Thread.sendData(1);
                }catch(Exception e)
                {
                    Log.w("Exception : ","Sending error"+e.toString());
                }
                break;
            }
        }*/
            }

        }
    }

}