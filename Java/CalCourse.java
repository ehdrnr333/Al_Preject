import java.util.Iterator;
import java.util.TreeSet;
import java.util.Vector;

import javax.swing.JOptionPane;

public class CalCourse 
{
	public static final int BOOL_MAX = 141;  //197(7일)

	int m_weight = 1;

	public int execute[];
	CourseList calList;
	Boolean[] m_arr= new Boolean[BOOL_MAX];   
	int calNum = 0;
	public TreeSet<Instance> insStorage = new TreeSet<Instance>();
	
	CalCourse(Vector<Course> _crsList)
	{
		calList = new CourseList(_crsList);
		execute = new int[calList.sSum];
	}
	void CreateInstanceList(Course _crs)
	{
		int cal = 1;
		int beforeCal = 1;
		Iterator itr2 = calList.sbjStorage.iterator();
		while(itr2.hasNext())
		{
			beforeCal = cal;
			Subject sbj = (Subject) itr2.next();
			cal *= (sbj.cSum+1);
			if(cal<beforeCal){
				if(JOptionPane.showConfirmDialog(null, "연산횟수를 초과합니다. 계속 진행하시겠습니까?\n(많은 시간이 소요될 수 있습니다. 문제가 발생하면 강제종료해주세요.)", "연산 시간", JOptionPane.WARNING_MESSAGE)==JOptionPane.OK_OPTION)
					break;
				else
					return;
			}
		}
		System.out.println(cal);
		long start = System.currentTimeMillis();
		while(true)
		{
			CreateInstance(_crs);
			if(ExecuteMaxCheck())
				break;
			NextExecute();
		}
		long end = System.currentTimeMillis();
		System.out.println(end-start);
		Iterator itr = insStorage.iterator();
		while(itr.hasNext())
		{
			Instance ins = (Instance)itr.next();
		}
	}
	
	void CreateInstance(Course _crs)
	{   
		ArrInit(_crs);  
		Instance ins = new Instance(insStorage);
		for(int i =0; i<calList.sSum; ++i)
		{
			Course crs = calList.sbjStorage.elementAt(i).crsStorage.elementAt(execute[i]);
			if(execute[i]>0&&TimeCal(crs))
			{   
				ins.m_creditSum += crs.credit;
				ins.m_priorSum += crs.prior;
				ins.m_key.add(crs.num);
				++ins.m_subNum;
			}
		}
		if(OverloadCheck(ins))
		{
			insStorage.add(ins);
		}
	}
	
	void ArrInit(Course _course)
	{
		
		for(int i = 0; i<BOOL_MAX; ++i)
			m_arr[i]=false;
		int s;
		Iterator titr = _course.timeStorage.iterator();
		for(int i = 0; i<_course.timeStorage.size(); ++i)
		{
			s = _course.timeStorage.elementAt(i).sIndex;
			while(s!=_course.timeStorage.elementAt(i).eIndex)
			{	
				m_arr[s]=true;++s;
			}
		}
	}
	boolean TimeCal(Course _course)
	{	int s;
		Iterator titr = _course.timeStorage.iterator();
		for(int i = 0; i<_course.timeStorage.size(); ++i)
		{
			s = _course.timeStorage.elementAt(i).sIndex;
			while(s<_course.timeStorage.elementAt(i).eIndex)
			{	
				if(m_arr[s]==false)
				{	m_arr[s]=true;++s;}
				else
				{
					--s;
					while(s>_course.timeStorage.elementAt(i).sIndex-1)
					{
						m_arr[s]=false;
						--s;
					}
					if(i!=0)
					{   
						for(int j=i-1; j>=0;--j)
						{
							s= _course.timeStorage.elementAt(j).eIndex-1;
							while(s>_course.timeStorage.elementAt(j).sIndex-1)
							{
								m_arr[s]=false;
								--s;
			}}}return false;
		}}}return true;
	}		
	boolean OverloadCheck(Instance _ins)
	{   
		if(this.insStorage.size()<15)
			return true;
		Instance ins = insStorage.last();
		if(ins.m_creditSum+ins.m_priorSum<_ins.m_creditSum+_ins.m_priorSum)
		{
			insStorage.pollLast();
			return true;
		}
		return false;
	}
	boolean ExecuteMaxCheck()
	{
		for(int i =0; i<calList.sSum; ++i)
		{   
			if(execute[i]<calList.sbjStorage.elementAt(i).cSum-1)
				return false;
		}
		return true;
	}
	void NextExecute()
	{	
		int numbering = calList.sSum-1;
		while(numbering>=0){
			if(execute[numbering]+1<calList.sbjStorage.elementAt(numbering).cSum)
			{
				++execute[numbering];
				return;
			}
			else
			{
				execute[numbering]=0;
				--numbering;
			}
		}
	}
}

class Instance implements Comparable<Instance>
{
	int m_creditSum=0;
	int m_priorSum=0;
	Vector<Integer> m_key = null;
	public int m_subNum=0;
	TreeSet<Instance> insStorage = null;
	Instance(TreeSet<Instance> _insStorage)
	{
		insStorage = _insStorage;
		m_key = new Vector<Integer>();
	}
	@Override
	public int compareTo(Instance _ins) {
		if(m_creditSum==_ins.m_creditSum&&m_subNum==_ins.m_subNum&&m_priorSum==_ins.m_priorSum)
		{
			for(int k = 0; k<m_subNum; ++k)
			{
				if(this.m_key.elementAt(k)!=_ins.m_key.elementAt(k))
					return -1;
			}
			return 0;
		}
		if(m_creditSum+m_priorSum+m_subNum>=_ins.m_creditSum+_ins.m_priorSum+m_subNum)
			return -1;
		else 
			return 1;
	}
	public void show()
	{
		Iterator itr = m_key.iterator();
		System.out.print(this.hashCode()+"::");
		System.out.print(this.m_subNum+"/"+this.m_creditSum+"/"+this.m_priorSum);
		while(itr.hasNext())
		{
			int i = (int)itr.next();
			System.out.print("["+i+"]");
		}
		System.out.println("");
	}
}