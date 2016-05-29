import java.util.Vector;

public class Subject
{
	public Vector<Course> crsStorage = new Vector<Course>();
	public String name;
	public int cSum = 0;
	public Subject(Course _c)
	{
		name = _c.name;
		this.addCourse(new Course());
		addCourse(_c);
	}
	public void addCourse(Course _c)
	{
		++cSum;
		crsStorage.add(_c);
	}
}