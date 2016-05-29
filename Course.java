import java.util.Iterator;
import java.util.Vector;

interface Week
{
	int MON=0, TUE=1, WED=2, THU=3, FRI=4, SAT=5, SUN=6;
}

public class Course 
{        
	public int num;
	public String name;     
	public int credit;  
	public int prior;   
	public String professor;
	public Vector<Time> timeStorage = new Vector<Time>();
	
	public Course()
	{
		
	}
	public Course(int _num, String _name, int _prior, int _credit, Vector<Time> _time, String _prof)
	{
		num = _num;
		name = _name;     
		prior = _prior;   
		credit = _credit; 
		timeStorage = _time;
		professor = _prof;
	}
	/*public String toString()
	{
		String str = name;
		for(int i = name.length(); i<11; ++i)
			str +="��";
		str += professor;
		for(int i = professor.length(); i<6; ++i)
			str +="��";
		str += credit+"�젏";
		for(int i = String.valueOf(credit).length(); i<3; ++i)
			str +="��";
		str += "以묒슂�룄["+prior+"]";
		for(int i = String.valueOf(prior).length(); i<3; ++i)
			str +="��";
		Iterator itr = timeStorage.iterator();
		while(itr.hasNext())
		{
			Time t = (Time)itr.next();
			str +=t.toString()+" ";
		}
		return str;
	}*/
	public void setNum(int _n)
	{
		num = _n;
	}
}

class Time 
{   
	public int wDay;     
	private int sHour;
	private int sMin;
	private int eHour;
	private int eMin;
	
	public int sIndex;
	public int eIndex;
	
	public Time(int _w, int _sT, int _eT)
	{
		wDay = _w;     
		sHour = _sT/2+8;
	 	sMin = (_sT%2)*30;
		eHour = _eT/2+8;
		eMin = (_eT%2)*30;
		
		sIndex = (wDay*28)+((sHour-8)*2)+1;
		eIndex = (wDay*28)+((eHour-8)*2)+1;
		
		if(sMin!=0)
			++sIndex;
		if(eMin!=0)
			++eIndex;
	}
	public String toString()
	{
		String str;
		switch(wDay)
		{
		case Week.MON:
			str = "�썡 ";
			break;
		case Week.TUE:
			str = "�솕 ";
			break;
		case Week.WED:
			str = "�닔 ";
			break;
		case Week.THU:
			str = "紐� ";
			break;
		case Week.FRI:
			str = "湲� ";
			break;
		/*case Week.SAT:
			str = "�넗 ";
			break;
		case Week.SUN:
			str = "�씪 ";
			break;*/
		default:
			return null;
		}
		str += sHour+"�떆 "+sMin+"遺� ~ "+eHour+"�떆 "+eMin+"遺�";
		return str;
	}
}