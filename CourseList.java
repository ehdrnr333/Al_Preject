import java.util.Iterator;
import java.util.Scanner;
import java.util.Vector;

public class CourseList {
	
	public Vector<Subject> sbjStorage = new Vector<Subject>();
	public static Scanner keyboard = new Scanner(System.in);
	public int sSum=0;
	public int cNum = 0;
	public CourseList(Vector<Course> _crsList)
	{
		Iterator itr = _crsList.iterator();
		while(itr.hasNext())
		{
			Course crs = (Course) itr.next();
			Add(crs);
		}
	}
	public void Add(Course _c)
	{
		Iterator titr = _c.timeStorage.iterator();
		while(titr.hasNext())
		{
			Time t = (Time)titr.next();
			if(t.sIndex>=t.eIndex||t.sIndex==0)
			{
				System.out.println("시간이 잘못된 수업");
				return;
			}
		}
		Iterator sitr = sbjStorage.iterator();
		while(sitr.hasNext())
		{
			Subject sbj = (Subject) sitr.next();
			System.out.println(_c.name+" :: "+sbj.name);
			if(_c.name.equals(sbj.name))
			{
				_c.setNum(++cNum);
				sbj.addCourse(_c);
				return;
			}
		}
		++sSum;
		_c.setNum(++cNum);
		Subject newSbj = new Subject(_c);
		sbjStorage.add(newSbj);
	}
}