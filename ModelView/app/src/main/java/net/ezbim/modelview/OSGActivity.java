package net.ezbim.modelview;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.graphics.AvoidXfermode;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;

import net.ezbim.modelview.R;

import java.util.ArrayList;

public class OSGActivity extends AppCompatActivity {
    private static final String TAG = "OSG Activity";
    private EBIMView mView;
    private AlertDialog loadLayerAddress;
    private EditText editText;
    private Toolbar toolbar;
    private ArrayList<String> floorNameList;
    private String address;

    // Main Android Activity life cycle
    @Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        setContentView(R.layout.activity_main);
        mView = (EBIMView) findViewById(R.id.eglview);
        toolbar = (Toolbar) findViewById(R.id.toolbar);
        floorNameList = new ArrayList<>();
        toolbar.setTitle(R.string.app_name);
        setSupportActionBar(toolbar);
        editText = new EditText(this);
        AlertDialog.Builder loadLayerDialogBuilder = new AlertDialog.Builder(this);
        loadLayerDialogBuilder.setTitle("输入文件路径").setView(editText).setNegativeButton("取消", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
            }
        }).setPositiveButton("确定", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                address = editText.getText().toString();
                if (address != null && !address.equals("")) {
                    int value1 = ModelView.loadObject(address);
//                    int value1 =  ModelView.preProcessBIMFile(address,true);
                    Log.e("preProcessBIMFile == "," "+value1);
                }
            }
        });
        loadLayerAddress = loadLayerDialogBuilder.create();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.mainmenu, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.loadpath:
                loadLayerAddress.show();
                break;
            case R.id.text:
                floorNameList = ModelView.getFloorNames();
                for(String fname:floorNameList){
                    Log.e("FloorName : ",fname);
                }
                break;
            case R.id.text2:
                if(floorNameList!=null && floorNameList.size()>0) {
                    ModelView.loadByFloorName(floorNameList.get(0));
                    ModelView.loadByFloorName(floorNameList.get(1));
//                    ModelView.loadByFloorName(floorNameList.get(2));
                }
                break;
            case R.id.text3:
                ModelView.loadObject(address);
                break;
            case R.id.text4:

                break;
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.e(TAG, "onPause");
        mView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.e(TAG, "onResume");
        mView.onResume();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.e(TAG, "onDestroy");
        ModelView.unLoadAll();
    }
}