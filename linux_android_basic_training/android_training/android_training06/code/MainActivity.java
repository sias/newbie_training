package com.example.muisc;

import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.ImageButton;

public class MainActivity extends Activity {
	private ImageButton mStartImageButton=null;
	public MediaPlayer mMediaPlayer =null;
	private static final String MUSIC_PATH=new String("/mnt/sdcard/love.mp3");
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mMediaPlayer = new MediaPlayer();
        mStartImageButton=(ImageButton)findViewById(R.id.Startbutton);
        mStartImageButton.setOnClickListener(new ImageButton.OnClickListener()
        {
        	public void onClick(View v)
        	{
        		playMusic(MUSIC_PATH);
        	}
        });        
    }
    private void playMusic(String path)
    {
    	try{
    		mMediaPlayer.reset();
    		mMediaPlayer.setDataSource(path);
    		mMediaPlayer.prepare();
    		mMediaPlayer.start();
    	}catch (IOException e){}   	
    }
    class MusicFilter implements FilenameFilter
    {

		@Override
		public boolean accept(File arg0, String arg1) {
			// TODO Auto-generated method stub
			return false;
		}	
    }
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }
}
