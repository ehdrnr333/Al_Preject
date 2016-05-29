import java.awt.Desktop;
import java.io.File;
import java.net.URL;

import javax.swing.ImageIcon;
import javax.swing.UIManager;

public class MainApp {

	public static void main(String[] args) {
		try 
		{
			UIManager.setLookAndFeel("javax.swing.plaf.nimbus.NimbusLookAndFeel");
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		MyFrame frame = new MyFrame("표도령        1.1");
	}
}