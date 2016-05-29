import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.*;
import java.net.URL;

import javax.imageio.ImageIO;
import javax.swing.*;

public class MyFrame extends JFrame
{
	public static Font font21 = new Font("나눔바른고딕", Font.PLAIN, 21);
	public static Font font20 = new Font("나눔바른고딕", Font.PLAIN, 20);
	public static Font font19 = new Font("나눔바른고딕", Font.PLAIN, 19);
	public static Font font18 = new Font("나눔바른고딕", Font.PLAIN, 18);
	public static Font font17 = new Font("나눔바른고딕", Font.PLAIN, 17);
	public static Font font16 = new Font("나눔바른고딕", Font.PLAIN, 16);
	public static Font font15 = new Font("나눔바른고딕", Font.PLAIN, 15);
	public static Font font14 = new Font("나눔바른고딕", Font.PLAIN, 14);
	public static Font font13 = new Font("나눔바른고딕", Font.PLAIN, 13);
	public static Font font12 = new Font("나눔바른고딕", Font.PLAIN, 12);
	private BufferedImage img;
	JLabel imgLabel = new JLabel();
	JLayeredPane startPane = new JLayeredPane();
	CourseLayer coursePane = new CourseLayer(this);
	TableLayer tablePane = new TableLayer(this);
	int changeLayer= 1;
	
	public MyFrame(String title)
	{	
		// Public Area
		super("표도령");
		
		setIconImage(Toolkit.getDefaultToolkit().getImage(getClass().getClassLoader().getResource("Icon.jpg")));
		setBounds(140,140,900,824);
		getContentPane().setLayout(new BorderLayout());
		
		this.setPreferredSize(getSize());
		
		try {
			URL url = getClass().getClassLoader().getResource("start.jpg");
            imgLabel.setIcon(new ImageIcon(url));
        } catch (Exception e) {
            System.out.println("이미지 불러오기 실패");
        }
		startPane.setLayout(new BorderLayout());
		startPane.add(imgLabel, BorderLayout.CENTER);
	
		getContentPane().add(startPane);
		setVisible(true);
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		Change();
		setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
		
		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		
		JMenu aboutMenu = new JMenu("about");
		menuBar.add(aboutMenu);
		
		JMenuItem mntmNewMenuItem = new JMenuItem("Ver 1.4.0");
		aboutMenu.add(mntmNewMenuItem);
		
		JMenuItem mntmNewMenuItem_1 = new JMenuItem("made by donggukYang");
		aboutMenu.add(mntmNewMenuItem_1);
		
	}
	private void setLayeredPane(BorderLayout borderLayout) {
		// TODO Auto-generated method stub
		
	}
	public void Change()
	{
		if(changeLayer==1)
		{
			getContentPane().removeAll();
			setVisible(false);
			changeLayer = 2;
			getContentPane().add(coursePane, BorderLayout.CENTER);
			setVisible(true);
		}
		else if(changeLayer == 2)
		{
			getContentPane().removeAll();
			setVisible(false);
			changeLayer = 3;
			getContentPane().add(tablePane, BorderLayout.CENTER);
			setVisible(true);
		}
		else
		{
			getContentPane().removeAll();
			setVisible(false);
			changeLayer = 2;
			getContentPane().add(coursePane, BorderLayout.CENTER);
			setVisible(true);
		}
	}
}

