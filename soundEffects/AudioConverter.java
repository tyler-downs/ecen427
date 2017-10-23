import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.security.InvalidParameterException;

import static java.lang.System.exit;


/**
 * Created by bondd on 10/23/2017.
 */

public class AudioConverter {


    public static void main(String args[]) throws Exception
    {
        if (args.length != 2) {
            System.out.println("Error: There should be 2 arguments provided. The input .wav file, and the output file without the extension");
            exit(0);
        }
        String filenameIn = args[0]; //the file we will be reading from
        String filenameOut = args[1]; //assuming it NOT is called with the ".c" extension

        int numSamples = 0; //the number of samples in the .wav file
        int sampleRate = 0; //the sample rate of the audio data

        InputStream inStream = new FileInputStream(new File(filenameIn));
        byte[] bytes_temp = new byte[4];

        inStream.skip(22); //bytes 22-23 is num channels
        inStream.read(bytes_temp, 0, 2); //read 2-byte value

        System.out.println("num channels: " + byteArrayToInt(bytes_temp));
       // inStream.skip(2); //bytes 24-27 will give us the sample rate

        inStream.read(bytes_temp, 0, 4); //0 is offset in byte array. The sample rate is a 4-byte integer.

        sampleRate = byteArrayToInt(bytes_temp); //convert little-endian byte array to an int
        System.out.println("sample rate: " + sampleRate);

        inStream.skip(6); //byte 34-35 gives us bits per sample
        inStream.read(bytes_temp, 0, 2);
        System.out.println("bits per sample: " + byteArrayToInt(bytes_temp));

        // number of bytes in data, shown at bytes 40-43
        inStream.skip(4); //get to byte 40 from 36
        inStream.read(bytes_temp, 0, 4); //read 4-byte value
        numSamples = byteArrayToInt(bytes_temp);
        System.out.println("number of data bytes: " + numSamples);



        //create output file
        PrintWriter out = new PrintWriter(filenameOut + ".c");
        out.write("#include <stdint.h>\n\n"); //add header
        out.write("int32_t " + filenameOut + "_sampleRate = " + sampleRate + ";\n");
        out.write("int32_t " + filenameOut + "_numSamples = " + numSamples + ";\n\n");

        out.write("int32_t " + filenameOut + "_soundData[] = {\n");

        int data;
        int wordsInLine = 0;
        int maxDataPerLine = 15;
        if ((data = inStream.read()) != -1) {
            out.write(Integer.toString(data));
        }
        while ( (data = inStream.read()) != -1)
        {
            out.write(", ");
            wordsInLine++;
            if (wordsInLine >= maxDataPerLine)
            {
                out.write("\n");
                wordsInLine = 0;
            }
            out.write(Integer.toString(data));
        }
        out.write("};");
        out.close();
    }

    private static int byteArrayToInt(byte[] b) //little-endian
    {
        if (b.length == 2)
            return b[0] & 0xFF |
                    (b[1] & 0xFF) << 8;
        if (b.length == 4)
            return   b[0] & 0xFF |
                (b[1] & 0xFF) << 8 |
                (b[2] & 0xFF) << 16 |
                (b[3] & 0xFF) << 24;

        return 0;
    }

}
