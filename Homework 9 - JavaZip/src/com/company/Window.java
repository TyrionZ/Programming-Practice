package com.company;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;


public class Window extends JFrame implements MouseListener {
	JLabel folderText, fileText, status;
	JTextField folderInput, fileInput;
	JButton packButton, unpackButton;
	PackTool packTool;
	JPanel row0, row1, row2;

	public Window() {
		super("Pack Tool");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new FlowLayout());

		fileText = new JLabel("File Path: ", JLabel.RIGHT);
		folderText = new JLabel("Folder Path: ", JLabel.RIGHT);
		fileInput = new JTextField("please enter the file's absolute path.");
		folderInput = new JTextField("please enter the folder's absolute path.");
		packButton = new JButton("Pack");
		unpackButton = new JButton("Unpack");
		status = new JLabel("waiting...", JLabel.CENTER);

		packButton.addMouseListener(this);
		unpackButton.addMouseListener(this);

		setLayout(new GridLayout(4, 1, 10, 10));

		row0 = new JPanel();
		row0.setLayout(new FlowLayout());
		row0.add(fileText);
		row0.add(fileInput);
		add(row0);

		row1 = new JPanel();
		row1.setLayout(new FlowLayout());
		row1.add(folderText);
		row1.add(folderInput);
		add(row1);

		row2 = new JPanel();
		row2.setLayout(new FlowLayout(FlowLayout.CENTER));
		row2.add(packButton);
		row2.add(unpackButton);
		add(row2);

		add(status);

		setSize(400, 200);
		setVisible(true);
	}

	public void mouseExited(MouseEvent e) {}
	public void mouseReleased(MouseEvent e) {}
	public void mousePressed(MouseEvent e) {}
	public void mouseEntered(MouseEvent e) {}

	public void mouseClicked(MouseEvent event) {
		if (event.getSource() == packButton) {
			try {
				packTool.pack(folderInput.getText(), fileInput.getText());
			} catch(Exception e) {
				JOptionPane notice = new JOptionPane();
				notice.showMessageDialog(this, e.getMessage());
			}
		}
		if (event.getSource() == unpackButton) {
			try {
				packTool.unpack(fileInput.getText(), folderInput.getText());
			} catch(Exception e) {
				JOptionPane notice = new JOptionPane();
				notice.showMessageDialog(this, e.getMessage());
			}
		}
	}

	public static void main( String args[])  {
		Window win = new Window();
		win.packTool = new PackTool(win);
	}
}
