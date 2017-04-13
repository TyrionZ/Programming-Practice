package com.test.test;

/**
 * Created by wulal on 2017/4/5.
 */

import java.io.*;
import java.util.Enumeration;
import java.util.zip.*;

public class Compress {
	public Compress() {}
	public void zip(String inputDir, String outFileName) throws Exception {
		System.out.println(outFileName);
		File inputFolder = new File(inputDir);
		ZipOutputStream out = new ZipOutputStream(new FileOutputStream(outFileName));
		process(out, inputFolder, "");
		System.out.println("zip done");
		out.close();
	}

	private void process(ZipOutputStream out, File f, String base) throws Exception {
		if (f.isDirectory()) {
			File[] fl = f.listFiles();
			out.putNextEntry(new ZipEntry(base + "/"));
			base = base.length() == 0 ? "" : base + "/";
			for (int i = 0; i < fl.length; i++) {
				process(out, fl[i], base + fl[i].getName());
			}
		} else {
			out.putNextEntry(new ZipEntry(base));
			FileInputStream in = new FileInputStream(f);
			int b;
			System.out.println(base);
			while ( (b = in.read()) != -1) {
				out.write(b);
			}
			in.close();
		}
	}

	public void unzip(String inputFileName, String outputDir) throws Exception {
		ZipFile file =  new ZipFile(inputFileName);
		byte[] buf = new byte[8192];
		Enumeration list = file.entries();
		ZipEntry entry;
		while (list.hasMoreElements()) {
			entry = (ZipEntry)list.nextElement();
			File currentFile = new File(outputDir + "/" + entry.getName());
			if (entry.isDirectory())
				currentFile.mkdir();
			else {
				OutputStream output = new BufferedOutputStream(new FileOutputStream(currentFile));
				InputStream input = new BufferedInputStream(file.getInputStream((entry)));
				int length = 0;
				while ((length = input.read(buf, 0, 8192)) != -1) {
					output.write(buf, 0, length);
				}
				input.close();
				output.close();
			}
		}
		file.close();
	}

//	public static void main(String [] temp){
//		Compress book = new Compress();
//		try {
//			book.zip("c://test0", "c://temp//test.zip");
//			book.unzip("c://temp//test.zip", "c://test1");//你要压缩的文件夹
//		} catch (Exception ex) {
//			ex.printStackTrace();
//		}
//	}
}
