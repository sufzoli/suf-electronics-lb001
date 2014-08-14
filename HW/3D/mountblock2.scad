difference()
{
	union()
	{
		cube([30,10,10]);
		translate([10,0,9.5])
			cube([10,10,5]);
	}
	
	translate([5,5,-0.5])
		cylinder(h=11,r=2, $fn=100);
	translate([5,5,8])
		cylinder(h=2.1,r1=2,r2=4.1, center=false, $fn=100);
	translate([25,5,-0.5])
		cylinder(h=11,r=2, $fn=100);
	translate([25,5,8])
		cylinder(h=2.1,r1=2,r2=4.1, center=false, $fn=100);
	translate([15,10.5,9.5])
	{
		rotate([90,0,0]) cylinder(h=11,r=1, $fn=100);
	}
}
