import java.awt.AWTException;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Desktop;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Iterator;
import java.util.Vector;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.Robot;
import java.awt.Toolkit;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
public class CourseLayer extends JLayeredPane
{
	public MyFrame mFrame = null;
	
	JPanel uCoursePanel = new JPanel();
	JPanel mCoursePanel = new JPanel();
	JPanel lCoursePanel= new JPanel();
	JPanel btnPanel = new JPanel();
	
	Color mainColor = new Color(238, 244,250);
	Color listColor = new Color(254, 255,255);
	Color btnColor = new Color(215, 230,250);
	Font mainFont = MyFrame.font21;
	Font tableFont = MyFrame.font17;
	
	public JTextField pathField = new JTextField();
	private JButton pathBtn = new JButton();
	
	private final JButton createButton = new JButton("생성(최대 소요시간 : 1분)");
	private final JButton tableButton = new JButton("시간표");
	private final JButton addButton = new JButton("수업추가");
	private final JButton modButton = new JButton("수업수정");
	private final JButton delButton = new JButton("수업삭제");
	private final JButton blankButton = new JButton("공강설정");
	
	public Vector<Course> crsStorage = new Vector<Course>();	
	public JList list = new JList();
	public CalCourse cal=null;
	public Course blank = new Course();
	public BlankFrame bFrame = null;
	public CourseLayer(MyFrame _frame)
	{
		mFrame = _frame;
		bFrame = new BlankFrame(this);
		setLayout(new BorderLayout());
		this.setPreferredSize(getSize());
		
		uCoursePanel.setBackground(mainColor);
		uCoursePanel.setLayout(new BorderLayout(0, 0));
		mCoursePanel.setBackground(mainColor);
		mCoursePanel.setLayout(new BorderLayout(0, 0));
		lCoursePanel.setBackground(mainColor);
		lCoursePanel.setLayout(new GridLayout(1, 0, 0, 0));
		
		// < Course Area >
		// Upper Pan
		pathField.setFont(MyFrame.font18);
		pathField.setBounds(14, 12, 400, 36);
		pathField.setColumns(10);
		pathBtn.setBackground(btnColor);
		pathBtn.setText("엑셀 파일");
		pathBtn.setFont(MyFrame.font18);
		pathBtn.setBounds(423, 12, 105, 36);
		pathBtn.addActionListener(new OpenActionListener(this));
		
		JLabel intro1 = new JLabel("  유드림스 엑셀파일을 불러옵니다.");
		intro1.setFont(MyFrame.font14);
		intro1.setBounds(540, 5, 400, 20);
		uCoursePanel.add(pathField, BorderLayout.CENTER);
		uCoursePanel.add(pathBtn, BorderLayout.EAST);
		uCoursePanel.add(intro1, BorderLayout.WEST);
		
		// Middle Pan
		addButton.setBackground(btnColor);
		addButton.setFont(mainFont);
		addButton.addActionListener(new AddEventHandler(this));
		modButton.setBackground(btnColor);
		modButton.setFont(mainFont);
		modButton.addActionListener(new ModEventHandler(this));
		delButton.setBackground(btnColor);
		delButton.setFont(mainFont);
		delButton.addActionListener(new DelEventHandler(this));
		blankButton.setBackground(btnColor);
		blankButton.setFont(mainFont);
		blankButton.addActionListener(new BlankEventHandler(this));
		
		list.setFont(new Font(null, Font.PLAIN, 24));
		list.setBackground(listColor);
		list.setListData(crsStorage);
		list.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
		
		btnPanel.setLayout(new GridLayout(0,4));
		btnPanel.setBackground(mainColor);
		btnPanel.add(addButton);
		btnPanel.add(modButton);
		btnPanel.add(delButton);
		btnPanel.add(blankButton);
		
		mCoursePanel.add(btnPanel, BorderLayout.NORTH);
		mCoursePanel.add(new JScrollPane(list), BorderLayout.CENTER);
		
		// Lower Pan
		createButton.setBackground(btnColor);
		createButton.setFont(mainFont);
		createButton.addActionListener(new CreateEventHandler(mFrame));
		tableButton.setBackground(btnColor);
		tableButton.setFont(mainFont);
		tableButton.addActionListener(new ConvertEventHandler(this));
		
		lCoursePanel.add(createButton);
		lCoursePanel.add(tableButton);
		
		add(uCoursePanel, BorderLayout.NORTH);
		add(mCoursePanel, BorderLayout.CENTER);
		add(lCoursePanel, BorderLayout.SOUTH);
	}
}
class OpenActionListener implements ActionListener{
	JFileChooser chooser;
	CourseLayer layer;
	Robot rb;
	OpenActionListener(CourseLayer _layer){
		chooser = new JFileChooser();
		layer = _layer;
	}
	public void actionPerformed(ActionEvent e){
		String userDir = System.getProperty("user.home");
		chooser = new JFileChooser(userDir +"/Desktop");
		int ret = chooser.showOpenDialog(null);
		if(ret != JFileChooser.APPROVE_OPTION){
			return;
		}
		String filePath = chooser.getSelectedFile().getPath();
		String text = "";
		layer.pathField.setText(filePath);
		
		// 엑셀 읽기
		try {
			rb = new Robot();
		} catch (AWTException e2) {
			// TODO Auto-generated catch block
			e2.printStackTrace();
		}
		File file = new File(filePath);
		try {
			Desktop.getDesktop().open(file);
			System.out.println("execute");
			rb.delay(2000);
		      // 메모장에 입력한 글자를 모두 선택한다.
		       rb.keyPress(KeyEvent.VK_CONTROL);
		       rb.keyPress(KeyEvent.VK_A);
		       rb.keyRelease(KeyEvent.VK_CONTROL);
		       rb.keyRelease(KeyEvent.VK_A);
		       System.out.println("모두 선택");

		      //현재 해당 쓰레드를 500ms 동안 sleep시킨다.
		       rb.delay(500);
		       rb.keyPress(KeyEvent.VK_CONTROL);
		       rb.keyPress(KeyEvent.VK_A);
		       rb.keyRelease(KeyEvent.VK_CONTROL);
		       rb.keyRelease(KeyEvent.VK_A);
		       System.out.println("모두 선택");

		      //현재 해당 쓰레드를 500ms 동안 sleep시킨다.
		       rb.delay(500);
		       
		       rb.keyPress(KeyEvent.VK_CONTROL);
		       rb.keyPress(KeyEvent.VK_C);
		       rb.keyRelease(KeyEvent.VK_CONTROL);
		       rb.keyRelease(KeyEvent.VK_C);
		       System.out.println("복사");

		      //현재 해당 쓰레드를 500ms 동안 sleep시킨다.
		       rb.delay(500);
		       
		       Transferable transfer = Toolkit.getDefaultToolkit().getSystemClipboard().getContents(null);

				if (transfer != null && transfer.isDataFlavorSupported(DataFlavor.stringFlavor)) 
				{ 
					text = (String)transfer.getTransferData(DataFlavor.stringFlavor);
				}
				if(text=="")
				{
					Desktop.getDesktop().open(file);
					rb.delay(2000);
				      // 메모장에 입력한 글자를 모두 선택한다.
				       rb.keyPress(KeyEvent.VK_CONTROL);
				       rb.keyPress(KeyEvent.VK_A);
				       rb.keyRelease(KeyEvent.VK_CONTROL);
				       rb.keyRelease(KeyEvent.VK_A);
				       System.out.println("모두 선택");

				      //현재 해당 쓰레드를 500ms 동안 sleep시킨다.
				       rb.delay(500);
				       rb.keyPress(KeyEvent.VK_CONTROL);
				       rb.keyPress(KeyEvent.VK_A);
				       rb.keyRelease(KeyEvent.VK_CONTROL);
				       rb.keyRelease(KeyEvent.VK_A);
				       System.out.println("모두 선택");

				      //현재 해당 쓰레드를 500ms 동안 sleep시킨다.
				       rb.delay(500);
				       
				       rb.keyPress(KeyEvent.VK_CONTROL);
				       rb.keyPress(KeyEvent.VK_C);
				       rb.keyRelease(KeyEvent.VK_CONTROL);
				       rb.keyRelease(KeyEvent.VK_C);
				       System.out.println("복사");

				      //현재 해당 쓰레드를 500ms 동안 sleep시킨다.
				       rb.delay(500);
				       
				       transfer = Toolkit.getDefaultToolkit().getSystemClipboard().getContents(null);

						if (transfer != null && transfer.isDataFlavorSupported(DataFlavor.stringFlavor)) 
						{ 
							text = (String)transfer.getTransferData(DataFlavor.stringFlavor);
						}
				}
		} 
		catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		catch (UnsupportedFlavorException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		String crs[] = text.split("\n");
		String element[][]= new String[crs.length][];
		for(int i = 1; i<crs.length; ++i)
		{
			element[i] = crs[i].split("\t");
			if(element[i].length<7||element[i][7]=="")
				continue;
			String time[] = element[i][7].split(",");
			String name = element[i][4];
			String professor = element[i][5];
			int credit = (int)Double.parseDouble(element[i][9]);
			int prio = 0;//Boolean.parseBoolean(element[i][2]);
			Vector<Time> timeStorage = new Vector<Time>();
			int before = 0;
			try
			{
			for(int j = 0; j<time.length; ++j)
			{
				String weekDay = time[j].substring(0, 1);
				double sNum = Double.parseDouble(time[j].substring(1, time[j].indexOf("-")));
				double eNum;
			
				if(time[j].contains("/"))
					eNum = Double.parseDouble(time[j].substring(time[j].indexOf("-")+1, time[j].indexOf("/")))+0.5;
				else
					eNum = Double.parseDouble(time[j].substring(time[j].indexOf("-")+1))+0.5;
				int week;
				switch(weekDay)
				{
				case "월":
					week = 0;
					break;
				case "화":
					week = 1;
					break;
				case "수":
					week = 2;
					break;
				case "목":
					week = 3;
					break;
				case "금":
					week = 4;
					break;
				/*case "토":
					week = 5;
					break;
				case "일":
					week = 6;
					break;*/
				default:
					week = before;
					break;
				}
				before = week;
				int sT= (int)sNum*2;
				int eT= (int)eNum*2;
				if(sNum%1!=0)++sT;
				if(eNum%1!=0)++eT;
				timeStorage.addElement(new Time(week, sT, eT));
				
			}
			}
			catch(Exception ex)
			{
				continue;
			}
			Course course = new Course(0, name,prio,credit, timeStorage, professor);
			System.out.println(course);
			layer.crsStorage.add(course);
		}
		layer.list.setListData(layer.crsStorage);
		if(layer.crsStorage.isEmpty())
			JOptionPane.showMessageDialog(null, "불러온 수업이 없습니다. 실행중인 엑셀파일이 있다면 껐다가 다시 불러와 주세요. \n※엑셀파일 실행 중에 다른 파일을 보고계시면 복사되지 않습니다", "엑셀파일 복사", JOptionPane.WARNING_MESSAGE);
		layer.mFrame.setEnabled(true);
		// 
	}
}

class AddEventHandler implements ActionListener
{
	InputFrame iFrame;
	CourseLayer layer;
	public AddEventHandler(CourseLayer _layer)
	{
		layer = _layer;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		iFrame = new InputFrame(layer, null);
		layer.setEnabled(false);
	}
}

class ModEventHandler implements ActionListener
{
	InputFrame iFrame;
	CourseLayer layer;
	public ModEventHandler(CourseLayer _layer)
	{
		layer = _layer;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		try
		{
			if(layer.list.isSelectionEmpty())
				throw new Exception();
		}
		catch(Exception _e)
		{
			System.out.println("선택된 컴포넌트가 없습니다.");
			return;
		}
		Course crs = layer.crsStorage.elementAt(layer.list.getSelectedIndex());
		iFrame = new InputFrame(layer, layer.crsStorage.elementAt(((layer.list.getSelectedIndex()))));
		layer.list.setListData(layer.crsStorage);
		layer.mFrame.setEnabled(true);
	}
}

class DelEventHandler implements ActionListener
{
	CourseLayer layer;
	int selec;
	public DelEventHandler(CourseLayer _layer)
	{
		layer = _layer;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		try
		{
			if(layer.list.isSelectionEmpty())
				throw new Exception();
		}
		catch(Exception _e)
		{
			System.out.println("선택된 컴포넌트가 없습니다.");
			return;
		}
		selec = layer.list.getSelectedIndex();
		layer.crsStorage.remove(selec);	
		layer.mFrame.setVisible(false);
		layer.mFrame.setVisible(true);
	}
}

class ConvertEventHandler implements ActionListener
{
	CourseLayer layer;
	public ConvertEventHandler(CourseLayer _layer)
	{
		layer = _layer;
	}
	public void actionPerformed(ActionEvent e)
	{
		layer.mFrame.Change();
	}
}

class CreateEventHandler implements ActionListener
{
	MyFrame frame;
	public CreateEventHandler(MyFrame _frame)
	{
		frame = _frame;
	}
	public void actionPerformed(ActionEvent e)
	{
		frame.tablePane.tableShift.removeAll();
		frame.coursePane.cal = new CalCourse(frame.coursePane.crsStorage);
		frame.coursePane.cal.CreateInstanceList(frame.coursePane.blank);
		
		frame.tablePane.addCard(frame);
		frame.Change();
	}
}
class BlankEventHandler implements ActionListener
{
	CourseLayer layer;
	public BlankEventHandler(CourseLayer _layer)
	{
		layer = _layer;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		layer.bFrame.setVisible(true);
		layer.setEnabled(false);
	}
}