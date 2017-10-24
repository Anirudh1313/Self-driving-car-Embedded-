package com.example.jay.googlemaprouter.Map;

import android.graphics.Color;

import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.model.PolylineOptions;

import java.util.ArrayList;

/**
 * Created by jay on 10/22/2017.
 */

public class MapCommands {


    public void drowline(ArrayList points, GoogleMap mMap)
    {
        PolylineOptions lineOptions = new PolylineOptions();
        lineOptions.addAll(points);
        lineOptions.width(12);
        lineOptions.color(Color.BLUE);
        lineOptions.geodesic(true);
        mMap.addPolyline(lineOptions);
    }

}
