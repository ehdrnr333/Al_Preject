import java.awt.*;
import java.awt.event.*;
import java.util.Vector;
import javax.swing.*;
import javax.swing.border.EtchedBorder;

public class BlankFrame extends JFrame
{
	public Course inputCourse = null;
	public CourseLayer layer = null;
	public Vector<Time> timeStorage = new Vector<Time>();
	public JComboBox prioField = new JComboBox();
	public JComboBox timeComb = null;
	public JComboBox startComb = null;
	public JComboBox endComb = null;
	
	// private 멤버
	private JPanel mainPanel = new JPanel();
	private JLabel mainLabel = new JLabel();
	private JLabel listLabel = new JLabel();
	private JLabel waveLabel = new JLabel();
	
	// button
	private JButton timeAddBtn = new JButton();
	private JButton removeBtn = new JButton();
	
	private JButton inputButton = new JButton();
	private JButton cancelButton = new JButton();
	
	// 콤보박스 원소
	private String time[] = {"8:00", "8:30", "9:00", "9:30", "10:00", "10:30", "11:00", "11:30", "12:00", "12:30", 
			"13:00", "13:30", "14:00", "14:30", "15:00", "15:30", "16:00", "16:30", "17:00", "17:30", 
			"18:00", "18:30", "19:00", "19:30", "20:00", "20:30", "21:00", "21:30"};
	Color mainColor = new Color(238, 244,250);
	Color listColor = new Color(254, 255,255);
	Color btnColor = new Color(215, 230,250);
	public Color s1Color = new Color(200, 200,200);
	public Color s2Color = new Color(160, 215,240);
	Font mainFont = MyFrame.font21;
	Font comboFont = MyFrame.font19;
	
	public JButton allBtn = null;
	public JButton monBtn = null;
	public JButton tueBtn = null;
	public JButton wedBtn = null;
	public JButton thuBtn = null;
	public JButton friBtn = null;
	public BlankFrame(CourseLayer _layer)
	{
		super("표도령");
		
		getContentPane().setBackground(mainColor);
		layer = _layer;
		
		setIconImage(Toolkit.getDefaultToolkit().getImage(getClass().getClassLoader().getResource("Icon.jpg")));
		setBounds(120,120,430,445);
		this.setPreferredSize(getSize());
		getContentPane().setLayout(null);

		mainLabel.setText("공강설정");
		mainLabel.setFont(MyFrame.font17);
		mainLabel.setBounds(14, 16, 112, 28);

		mainPanel.setBackground(listColor);
		mainPanel.setLayout(null);
		mainPanel.setBorder(new EtchedBorder());
		mainPanel.setBounds(0, 66, 412, 265);
		
		listLabel.setText("공강목록");
		listLabel.setFont(MyFrame.font17);
		listLabel.setBounds(17, 24, 68, 18);
		
		waveLabel.setText("~");
		waveLabel.setFont(new Font(null, Font.BOLD, 23));
		waveLabel.setBounds(179, 212, 21, 18);
		
		timeComb = new JComboBox(timeStorage);
		timeComb.setBackground(mainColor);
		timeComb.setFont(comboFont);
		timeComb.setBounds(17, 52, 282, 42);
		timeComb.setMaximumRowCount(5);
		
		startComb = new JComboBox(time);
		startComb.setBackground(mainColor);
		startComb.setFont(MyFrame.font16);
		startComb.setBounds(78, 197, 92, 49);
		
		endComb = new JComboBox(time);
		endComb.setBackground(mainColor);
		endComb.setFont(MyFrame.font16);
		endComb.setBounds(207, 197, 92, 49);
		
		timeAddBtn.setBackground(btnColor);
		timeAddBtn.setFont(MyFrame.font17);
		timeAddBtn.setText("추가");
		timeAddBtn.setBounds(319, 204, 63, 42);
		timeAddBtn.addActionListener(new BlankAddEventHandler(this));
		
		removeBtn.setText("삭제");
		removeBtn.setFont(MyFrame.font17);
		removeBtn.setBackground(new Color(215, 230, 250));
		removeBtn.setBounds(313, 52, 69, 42);
		removeBtn.addActionListener(new BlankRemoveEventHandler(this));
		
		// 버튼
		inputButton.setBackground(btnColor);
		inputButton.setText("입력");
		inputButton.setFont(MyFrame.font21);
		inputButton.setBounds(56, 343, 131, 43);
		inputButton.addActionListener(new inputBlankHandler(layer, this));
		cancelButton.setBackground(btnColor);
		
		cancelButton.setText("취소");
		cancelButton.setFont(mainFont);
		cancelButton.setBounds(224, 343, 131, 43);
		cancelButton.addActionListener(new cancelEventHandler(layer, this));
		
		mainPanel.add(listLabel);
		mainPanel.add(waveLabel);
		mainPanel.add(timeComb);
		mainPanel.add(startComb);
		mainPanel.add(endComb);
		mainPanel.add(timeAddBtn);
		mainPanel.add(removeBtn);
		getContentPane().add(cancelButton);
		getContentPane().add(inputButton);
		getContentPane().add(mainLabel);
		getContentPane().add(mainPanel);
		
		allBtn = new JButton("전체");
		allBtn.setFont(MyFrame.font16);
		allBtn.setBounds(17, 137, 65, 49);
		allBtn.setBackground(s1Color);
		allBtn.addActionListener(new AllPressEvent(this, allBtn));
		mainPanel.add(allBtn);
		
		
		JLabel addLabel = new JLabel();
		addLabel.setText("공강추가");
		addLabel.setFont(MyFrame.font17);
		addLabel.setBounds(17, 107, 80, 18);
		mainPanel.add(addLabel);
		
		monBtn = new JButton("월");
		monBtn.setFont(MyFrame.font16);
		monBtn.setBounds(90, 137, 50, 50);
		monBtn.addActionListener(new PressEvent(monBtn, allBtn, this));
		monBtn.setBackground(s1Color);
		mainPanel.add(monBtn);

		tueBtn = new JButton("화");
		tueBtn.setFont(MyFrame.font16);
		tueBtn.setBounds(154, 137, 50, 50);
		tueBtn.addActionListener(new PressEvent(tueBtn, allBtn, this));
		tueBtn.setBackground(s1Color);
		mainPanel.add(tueBtn);
		
		wedBtn = new JButton("수");
		wedBtn.setFont(MyFrame.font16);
		wedBtn.setBounds(218, 137, 50, 50);
		wedBtn.addActionListener(new PressEvent(wedBtn, allBtn, this));
		wedBtn.setBackground(s1Color);
		mainPanel.add(wedBtn);
		
		thuBtn = new JButton("목");
		thuBtn.setFont(MyFrame.font16);
		thuBtn.setBounds(282, 137, 50, 50);
		thuBtn.addActionListener(new PressEvent(thuBtn, allBtn, this));
		thuBtn.setBackground(s1Color);
		mainPanel.add(thuBtn);
		
		friBtn= new JButton("금");
		friBtn.setFont(MyFrame.font16);
		friBtn.setBounds(346, 137, 50, 50);
		friBtn.addActionListener(new PressEvent(friBtn, allBtn, this));
		friBtn.setBackground(s1Color);
		mainPanel.add(friBtn);
	}
}

class inputBlankHandler implements ActionListener
{
	CourseLayer mFrame = null;
	BlankFrame bFrame = null;
	public inputBlankHandler(CourseLayer _layer, BlankFrame _bframe)
	{
		mFrame = _layer;
		bFrame = _bframe;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		mFrame.blank.timeStorage = bFrame.timeStorage;
		mFrame.setEnabled(true);
		bFrame.dispose();
	}
}

class AllPressEvent implements ActionListener
{
	JButton btn = null;
	BlankFrame frame = null;
	public AllPressEvent(BlankFrame _frm, JButton _btn)
	{
		frame= _frm;
		btn = _btn;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		if(btn.getBackground()==frame.s1Color)
		{
			frame.monBtn.setBackground(frame.s2Color);
			frame.tueBtn.setBackground(frame.s2Color);
			frame.wedBtn.setBackground(frame.s2Color);
			frame.thuBtn.setBackground(frame.s2Color);
			frame.friBtn.setBackground(frame.s2Color);
			btn.setBackground(frame.s2Color);
		}
		else
		{
			frame.monBtn.setBackground(frame.s1Color);
			frame.tueBtn.setBackground(frame.s1Color);
			frame.wedBtn.setBackground(frame.s1Color);
			frame.thuBtn.setBackground(frame.s1Color);
			frame.friBtn.setBackground(frame.s1Color);
			btn.setBackground(frame.s1Color);
		}
	}
}
class PressEvent implements ActionListener
{
	JButton btn = null;
	JButton btn2 = null;
	BlankFrame frame = null;
	public PressEvent(JButton _btn, JButton _btn2, BlankFrame _frame)
	{
		btn= _btn;
		btn2= _btn2;
		frame = _frame;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		if(btn.getBackground()==frame.s1Color)
			btn.setBackground(frame.s2Color);
		else
		{
			btn.setBackground(frame.s1Color);
			btn2.setBackground(frame.s1Color);
		}
	}
}

class BlankAddEventHandler implements ActionListener
{
	BlankFrame frame = null;
	public BlankAddEventHandler(BlankFrame _bframe)
	{
		frame = _bframe;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		if(frame.monBtn.getBackground()==frame.s2Color)
			frame.timeStorage.add(new Time(0,frame.startComb.getSelectedIndex(), frame.endComb.getSelectedIndex()));
		if(frame.tueBtn.getBackground()==frame.s2Color)
			frame.timeStorage.add(new Time(1,frame.startComb.getSelectedIndex(), frame.endComb.getSelectedIndex()));
		if(frame.wedBtn.getBackground()==frame.s2Color)
			frame.timeStorage.add(new Time(2,frame.startComb.getSelectedIndex(), frame.endComb.getSelectedIndex()));
		if(frame.thuBtn.getBackground()==frame.s2Color)
			frame.timeStorage.add(new Time(3,frame.startComb.getSelectedIndex(), frame.endComb.getSelectedIndex()));
		if(frame.friBtn.getBackground()==frame.s2Color)
			frame.timeStorage.add(new Time(4,frame.startComb.getSelectedIndex(), frame.endComb.getSelectedIndex()));
	}
}

class BlankRemoveEventHandler implements ActionListener
{
	BlankFrame bFrame = null;
	public BlankRemoveEventHandler(BlankFrame _bframe)
	{
		bFrame = _bframe;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		bFrame.timeStorage.removeElement(bFrame.timeComb.getSelectedItem());
		bFrame.timeComb.setSelectedItem(null);
	}
}