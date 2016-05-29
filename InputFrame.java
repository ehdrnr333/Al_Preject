import java.awt.*;
import java.awt.event.*;
import java.util.Vector;
import javax.swing.*;
import javax.swing.border.EtchedBorder;

public class InputFrame extends JFrame
{
	public Course inputCourse = null;
	public CourseLayer layer = null;
	public Vector<Time> timeStorage = new Vector<Time>();
	
	// public 멤버
	public JTextField nameField;
	public JComboBox prioField = new JComboBox();
	public JComboBox creditComb = null;
	public JComboBox timeComb = null;
	public JComboBox weekComb = null;
	public JComboBox startComb = null;
	public JComboBox endComb = null;
	
	// private 멤버
	private JLabel mainLabel = new JLabel();
	
	private JPanel namePanel = new JPanel();
	private JLabel nameLabel = new JLabel();
	
	private JPanel creditPanel = new JPanel();
	private JLabel creditLabel = new JLabel();
	private JLabel prioLabel = new JLabel();
	
	private JPanel timePanel = new JPanel();
	private JLabel timeLabel = new JLabel();
	private JLabel waveLabel = new JLabel();
	
	// button
	private JButton timeAddBtn = new JButton();
	private JButton removeBtn = new JButton();
	
	private JButton inputButton = new JButton();
	private JButton cancelButton = new JButton();
	
	// 콤보박스 원소
	private String prio[] = {"0","10","20","30","40","50"};
	private String credit[] = {"0","1","2","3","4","5"};
	private String week[] = {"MON","TUE","WED","THU","FRI"};//SAT SUN
	private String time[] = {"8:00", "8:30", "9:00", "9:30", "10:00", "10:30", "11:00", "11:30", "12:00", "12:30", 
			"13:00", "13:30", "14:00", "14:30", "15:00", "15:30", "16:00", "16:30", "17:00", "17:30", 
			"18:00", "18:30", "19:00", "19:30", "20:00", "20:30", "21:00", "21:30"};
	Color mainColor = new Color(238, 244,250);
	Color listColor = new Color(254, 255,255);
	Color btnColor = new Color(215, 230,250);
	Font mainFont = MyFrame.font20;
	Font comboFont = MyFrame.font18;
	public JTextField profText = new JTextField();
	private JLabel profLabel = new JLabel();
	public InputFrame(CourseLayer _layer, Course _crs)
	{
		super("표도령");
		
		getContentPane().setBackground(mainColor);
		layer = _layer;
		
		setIconImage(Toolkit.getDefaultToolkit().getImage(getClass().getClassLoader().getResource("Icon.jpg")));
		setBounds(120,120,412,445);
		this.setPreferredSize(getSize());
		getContentPane().setLayout(null);
		inputCourse = _crs;
			
		// 메인 라벨
		mainLabel.setText("수업정보");
		mainLabel.setFont(comboFont);
		mainLabel.setBounds(14, 12, 112, 28);
		
		// 수업명 판넬
		namePanel.setBackground(listColor);
		namePanel.setBorder(new EtchedBorder());
		namePanel.setBounds(0, 52, 412, 76);
		namePanel.setLayout(null);
		
		nameLabel.setText("수업명");
		nameLabel.setFont(MyFrame.font17);
		nameLabel.setBounds(14, 30, 62, 18);
		
		nameField = new JTextField();
		nameField.setFont(MyFrame.font17);
		nameField.setBounds(76, 22, 294, 36);
		nameField.setColumns(10);
		
		// 학점 판넬
		creditPanel.setBackground(listColor);
		creditPanel.setLayout(null);
		creditPanel.setBorder(new EtchedBorder());
		creditPanel.setBounds(0, 127, 412, 70);
		
		creditLabel.setText("학점");
		creditLabel.setFont(MyFrame.font17);
		creditLabel.setBounds(14, 30, 62, 18);
		
		prioLabel.setText("중요도");
		prioLabel.setFont(MyFrame.font17);
		prioLabel.setBounds(124, 30, 51, 18);
		
		creditComb = new JComboBox(credit);
		creditComb.setBackground(mainColor);
		creditComb.setFont(comboFont);
		creditComb.setBounds(55, 12, 62, 46);
		
		prioField = new JComboBox(prio);
		prioField.setBackground(mainColor);
		prioField.setFont(comboFont);
		prioField.setBounds(181, 12, 62, 46);
		
		
		profLabel.setText("교수");
		profLabel.setFont(MyFrame.font17);
		profLabel.setBounds(257, 30, 34, 18);
		
		
		profText.setFont(MyFrame.font19);
		profText.setColumns(10);
		profText.setBounds(297, 22, 82, 36);
		
		// 시간 판넬
		timePanel.setBackground(listColor);
		timePanel.setLayout(null);
		timePanel.setBorder(new EtchedBorder());
		timePanel.setBounds(0, 196, 412, 135);
		
		timeLabel.setText("시간");
		timeLabel.setFont(MyFrame.font17);
		timeLabel.setBounds(14, 23, 39, 18);
		
		waveLabel.setText("~");
		waveLabel.setFont(new Font(null, Font.BOLD, 24));
		waveLabel.setBounds(184, 81, 21, 18);
		
		weekComb = new JComboBox(week);
		weekComb.setBackground(mainColor);
		weekComb.setFont(MyFrame.font16);
		weekComb.setBounds(14, 66, 72, 49);
		
		startComb = new JComboBox(time);
		startComb.setBackground(mainColor);
		startComb.setFont(MyFrame.font16);
		startComb.setBounds(89, 66, 92, 49);
		
		endComb = new JComboBox(time);
		endComb.setBackground(mainColor);
		endComb.setFont(MyFrame.font16);
		endComb.setBounds(207, 66, 92, 49);
		timeAddBtn.setBackground(btnColor);
		timeAddBtn.setFont(MyFrame.font17);
		
		timeAddBtn.setText("추가");
		timeAddBtn.setBounds(316, 73, 63, 42);
		timeAddBtn.addActionListener(new timeAddEventHandler(this));
		
		removeBtn.setText("삭제");
		removeBtn.setFont(MyFrame.font17);
		removeBtn.setBackground(new Color(215, 230, 250));
		removeBtn.setBounds(316, 12, 63, 42);
		removeBtn.addActionListener(new timeRemoveEventHandler(this));
		
		// 버튼
		inputButton.setBackground(btnColor);
		inputButton.setText("입력");
		inputButton.setFont(MyFrame.font21);
		inputButton.setBounds(56, 343, 131, 43);
		inputButton.addActionListener(new inputEventHandler(layer, this));
		cancelButton.setBackground(btnColor);
		
		cancelButton.setText("취소");
		cancelButton.setFont(mainFont);
		cancelButton.setBounds(224, 343, 131, 43);
		cancelButton.addActionListener(new cancelEventHandler(layer, this));
		
		if(_crs !=null)
		{
			nameField.setText(_crs.name);
			creditComb.setSelectedItem(Integer.toString(_crs.credit));
			prioField.setSelectedItem(Integer.toString(_crs.prior/10));
			profText.setText(_crs.professor);
			timeStorage = _crs.timeStorage;
		}
		
		timeComb = new JComboBox(timeStorage);
		timeComb.setBackground(mainColor);
		timeComb.setFont(comboFont);
		timeComb.setBounds(69, 12, 220, 42);
		timeComb.setMaximumRowCount(5);
		
		
		creditPanel.add(profLabel);
		namePanel.add(nameLabel);
		namePanel.add(nameField);
		creditPanel.add(creditLabel);
		creditPanel.add(prioLabel);
		creditPanel.add(creditComb);
		creditPanel.add(prioField);
		creditPanel.add(profText);
		timePanel.add(timeLabel);
		timePanel.add(waveLabel);
		timePanel.add(timeComb);
		timePanel.add(weekComb);
		timePanel.add(startComb);
		timePanel.add(endComb);
		timePanel.add(timeAddBtn);
		timePanel.add(removeBtn);
		getContentPane().add(cancelButton);
		getContentPane().add(inputButton);
		getContentPane().add(mainLabel);
		getContentPane().add(namePanel);
		getContentPane().add(creditPanel);
		getContentPane().add(timePanel);
		
		setVisible(true);
	}
}

class inputEventHandler implements ActionListener
{
	CourseLayer mFrame = null;
	InputFrame iFrame = null;
	public inputEventHandler(CourseLayer _layer, InputFrame _iframe)
	{
		mFrame = _layer;
		iFrame = _iframe;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		if(iFrame.inputCourse != null)
		{
			iFrame.inputCourse.name = iFrame.nameField.getText();
			iFrame.inputCourse.credit = Integer.parseInt(iFrame.creditComb.getSelectedItem().toString());
			iFrame.inputCourse.prior = Integer.parseInt(iFrame.prioField.getSelectedItem().toString());
			iFrame.inputCourse.timeStorage = iFrame.timeStorage;
			iFrame.inputCourse.professor = iFrame.profText.getText();
		}
		else
		{

		iFrame.inputCourse = new Course(0, iFrame.nameField.getText(), 
				Integer.parseInt(iFrame.prioField.getSelectedItem().toString()),
				Integer.parseInt(iFrame.creditComb.getSelectedItem().toString()),
				iFrame.timeStorage, 
				iFrame.profText.getText());
		mFrame.crsStorage.add(iFrame.inputCourse);
		}
		mFrame.list.setListData(mFrame.crsStorage);
		mFrame.setEnabled(true);
		iFrame.dispose();
	}
}

class cancelEventHandler implements ActionListener
{
	CourseLayer layer = null;
	JFrame Frame = null;
	public cancelEventHandler(CourseLayer _layer, JFrame _iframe)
	{
		layer = _layer;
		Frame = _iframe;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		layer.setEnabled(true);
		Frame.dispose();
	}
}

class timeAddEventHandler implements ActionListener
{
	InputFrame iFrame = null;
	public timeAddEventHandler(InputFrame _iframe)
	{
		iFrame = _iframe;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		iFrame.timeStorage.add(new Time(iFrame.weekComb.getSelectedIndex(),iFrame.startComb.getSelectedIndex(), iFrame.endComb.getSelectedIndex()));
	}
}

class timeRemoveEventHandler implements ActionListener
{
	InputFrame iFrame = null;
	public timeRemoveEventHandler(InputFrame _iframe)
	{
		iFrame = _iframe;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		iFrame.timeStorage.removeElement(iFrame.timeComb.getSelectedItem());
		iFrame.timeComb.setSelectedItem(null);
	}
}