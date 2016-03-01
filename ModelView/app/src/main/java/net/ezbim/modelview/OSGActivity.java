package net.ezbim.modelview;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.text.TextUtils;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class OSGActivity extends AppCompatActivity{
    private static final String TAG = "OSG Activity";
    private AlertDialog loadLayerAddress;
    private EBIMView mView;
    private EditText editText;
    private Toolbar toolbar;
    EBIMRenderer ebimRenderer;
    private ArrayList<String> floorNameList;
    private String checkedValue;
    private HashMap<String, ArrayList<String>> viewMap;

    // Main Android Activity life cycle
    @Override
    protected void onCreate(Bundle icicle) {
        Log.e(TAG, "onCreate");
        super.onCreate(icicle);
        setContentView(R.layout.activity_main);
        viewMap = new HashMap<>();
        mView = (EBIMView) findViewById(R.id.eglview);
        //
        ebimRenderer = new EBIMRenderer(mView.getViewWidth(), mView.getViewHeigh(), new EBIMRenderer.ModelViewListener() {
            @Override
            public void onInitFinished() {
                mView.openRender();
            }
            @Override
            public void onModelReload() {

            }
        });
        //
        mView.setSingleTapUpListener(new EBIMView.singleTapUpListener() {
            @Override
            public void IsSingelTagUp(String singleValue) {
                checkedValue = singleValue;
                Log.e(TAG,"SingleValue == "+singleValue);
            }
        });
        ebimRenderer.setIsinit(true);
        mView.setRenderer(ebimRenderer);
        mView.setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
        toolbar = (Toolbar) findViewById(R.id.toolbar);
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
                String address = editText.getText().toString();
                if (address != null && !address.equals("")) {
                    int value1 = ModelView.loadObject(address);
                    Log.e("loadObject == ", " " + value1);
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
                for (String fname : floorNameList) {
                    Log.e("FloorName : ", fname);
                }
                break;
            case R.id.text2:
                if (floorNameList != null && floorNameList.size() > 0) {
                    ModelView.loadByFloorName(floorNameList.get(0));
//                    ModelView.loadByFloorName(floorNameList.get(1));
                }
                mView.godEyes();
                break;
            case R.id.text3:
//                if(!TextUtils.isEmpty(checkedValue)) {
//                    Log.e(TAG,"1== "+checkedValue);
//                    ModelView.hiddenOtherEntities(checkedValue);
//                }
                viewMap = ModelView.getViewportCameraView();
                break;
            case R.id.text4:
//                if(!TextUtils.isEmpty(checkedValue)) {
//                    Log.e(TAG,"2== "+checkedValue);
//                    ModelView.unHiddenOtherEntities(checkedValue);
//                }
                if(viewMap!=null && viewMap.size()>0)
                    ModelView.zoomToViewPortCenter(viewMap);
                break;
            default:
                break;
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onPause() {
        Log.e(TAG, "onPause");
        super.onPause();
        mView.onPause();
        mView.closeRender();
    }

    @Override
    protected void onResume() {
        Log.e(TAG, "onResume");
        super.onResume();
        mView.onResume();
        mView.openRender();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.e(TAG, "onDestroy");
        ModelView.unLoadAll();
        mView.closeRender();
    }

    @Override
    public void onLowMemory() {
        Log.e(TAG, "onLowMemory");
        super.onLowMemory();
    }

    @Override
    protected void onStop() {
        Log.e(TAG, "onStop");
        super.onStop();
    }
}