public class Circle extends Shape
{
    public Circle( double rad )
    {
        radius = rad;
    }
    
    public double area( )
    {
        return Math.PI * radius * radius;
    }
    
    public double perimeter( )
    {
        return 2 * Math.PI * radius;
    }
    
    public String toString( )
    {
        return "Circle: " + radius;
    }
    
    private double radius;
}
