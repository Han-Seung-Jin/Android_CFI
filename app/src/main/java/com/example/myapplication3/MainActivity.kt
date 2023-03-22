package com.example.myapplication3

import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import java.io.InputStream
import java.io.FileOutputStream
import java.io.IOException

class MainActivity : AppCompatActivity() {

    //private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        //binding = ActivityMainBinding.inflate(layoutInflater)
        //setContentView(binding.root)
        try {
            val inputStream: InputStream = assets.open("payload.txt")
            val outputStream: FileOutputStream = openFileOutput("payload.txt", MODE_PRIVATE)
            val buffer = ByteArray(1024)
            var length: Int
            while (inputStream.read(buffer).also { length = it } > 0) {
                outputStream.write(buffer, 0, length)
            }
            outputStream.flush()
            outputStream.close()
            inputStream.close()
        } catch (e: IOException) {
            e.printStackTrace()
        }

        val btn: Button = findViewById(R.id.btn1)


        //Example of a call to a native method
        btn.setOnClickListener {
            btn.text = sumFromCustomJNI()
        }
    }

    /**
     * A native method that is implemented by the 'myapplication3' native library,
     * which is packaged with this application.
     */

    external fun sumFromCustomJNI() : String

    companion object {
        // Used to load the 'myapplication3' library on application startup.
        init {
            System.loadLibrary("libhello-jnicallback")
        }
    }
}