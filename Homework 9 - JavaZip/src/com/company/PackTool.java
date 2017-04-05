package com.company;

import java.io.*;
import java.time.Instant;
import java.util.*;
import java.nio.file.attribute.*;
import java.nio.file.*;

public class PackTool implements Serializable {
	Window window;

	PackTool(Window w) {
		window = w;
	}

	class PackedFile implements Serializable {
		String path;
		byte context[] = null;
		boolean isDirectory = false;

		Instant lastModifiedTime, creationTime;

		void readFile(File file) throws Exception {
			FileInputStream in = new FileInputStream(file.getAbsolutePath());
			ByteArrayOutputStream out = new ByteArrayOutputStream();

			byte buffer[] = new byte[8192];
			int  readLength;
			while ((readLength = in.read(buffer, 0, 8192)) != -1)
				out.write(buffer, 0, readLength);
			context = out.toByteArray();
			out.close();
			in.close();
		}

		public PackedFile(String root, File file) throws Exception {
			String absolutePath = file.getAbsolutePath();
			path = absolutePath.substring(root.length());

			Path p = Paths.get(file.getAbsolutePath());
			BasicFileAttributes attr = Files.readAttributes(p, BasicFileAttributes.class);
			lastModifiedTime = attr.lastModifiedTime().toInstant();
			creationTime = attr.creationTime().toInstant();

			if (file.isDirectory()) {
				window.status.setText("Entry " + path);
				isDirectory = true;
			}
			else {
				window.status.setText("Packing " + path);
				readFile(file);
			}
		}

		public void write(String root) throws Exception {
			String absolutePath = root + path;
			File file = new File(absolutePath);
			if (isDirectory) {
				window.status.setText("Entry " + path);
				if (!file.exists()) file.mkdir();
			}
			else {
				window.status.setText("Unpacking " + path);

				file.createNewFile();
				FileOutputStream out = new FileOutputStream(file);
				out.write(context, 0, context.length);
				out.flush();
				out.close();
			}

			Path p = Paths.get(absolutePath);
			BasicFileAttributeView view = Files.getFileAttributeView(p, BasicFileAttributeView.class);
			view.setTimes(FileTime.from(lastModifiedTime), null, FileTime.from(creationTime));
		}
	}

	public void pack(String inputDir, String outputFileName) throws Exception {
		File folder = new File(inputDir);
		if (!folder.exists())
			throw new RuntimeException("Folder doesn't exists!");
		if (folder.isFile())
			throw new RuntimeException("Isn't a folder!");

		window.status.setText("Start packing...");

		ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(new File(outputFileName)));

		out.writeInt(count(folder));
		traverse(out, inputDir, folder);

		window.status.setText("Packing completed!");
	}

	private int count(File file) {
		int res = 1;
		if (file.isDirectory()) {
			File f[] = file.listFiles();
			for (File i : f)
				res += count(i);
		}
		return res;
	}

	private void traverse(ObjectOutputStream out, String root, File file) throws Exception {
		out.writeObject(new PackedFile(root, file));
		if (file.isDirectory()) {
			File f[] = file.listFiles();
			for (File i : f)
				traverse(out, root, i);
		}
	}

	public void unpack(String inputFileName, String OutputDir) throws Exception {
		File file = new File(inputFileName);
		if (!file.exists())
			throw new RuntimeException("File doesn't exist!");
		if (file.isDirectory())
			throw new RuntimeException("Isn't a file!");

		window.status.setText("Start unpacking...");

		ObjectInputStream in = new ObjectInputStream(new FileInputStream(new File(inputFileName)));

		int total = in.readInt();
		ArrayList<PackedFile> folders = new ArrayList<PackedFile>();
		for (int i = 0; i < total; ++i) {
			PackedFile f = (PackedFile) in.readObject();
			f.write(OutputDir);
			if (f.isDirectory)
				folders.add(f);
		}
		for (int i = folders.size() - 1; i >= 0; i--)
			folders.get(i).write(OutputDir);


		window.status.setText("Unpacking completed!");
	}
}
