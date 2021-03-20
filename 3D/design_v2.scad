
l_slide = 200;
u_slide = 100;

// Side Panels
for(j=[5,70])
    for(i=[-220,200])
        translate([i,-130,j])
            %cube([20,260,60]);

// bottom, mid, top panels
for(i=[0,65,130])
translate([-220,-130,i])
    %cube([440,260,5]);

// back panel
translate([-220,130,0])
    %cube([440,5,135]);

// front panel
translate([-220,-135,0])
    difference()
    {
        cube([440,5,135]);
        translate([-1,-1,-1])
            cube([321,7,96]);
        translate([344,-1,98])
            cube([52,7,19]);
        for(i=[347.5:15:396])
        translate([i,6,87.5])
            rotate([90,0,0])
            cylinder(h=7, r=3, $fn=100);
    }


// lower drawer
translate([0,-1*l_slide,0])
{
    // drawer bottom
    translate([-195,-129,15])
        %cube([290,255,5]);
    // drawer front
    translate([-220,-135,0])
        cube([320,5,67.5]);
    // drawer front L join
    translate([-195,-130,14])
        %union()
        {
            %cube([290,1,15]);
            %cube([290,15,1]);
        }
    // Handle
    translate([-220,-151,14])
        %difference()
        {
            cube([320,15,15]);
            translate([-1,1.5,-1.5])
            cube([322,12,15]);
        }        
    // drawer back L
    translate([-195,126,13])
        %union()
        {
            cube([290,2,40]);
            translate([0,-18,0])
            cube([290,20,2]);
        }
    // drawer left side
    translate([-197,-129,13])
        %union()
        {
            cube([2,255,40]);
            cube([20,255,2]);
        }
    // drawer right side
    translate([95,-129,13])
        %union()
        {
            cube([2,255,40]);
            translate([-20,0,0])
            cube([20,255,2]);
        }   
        
}


// upper drawer

translate([0,-1*u_slide,0])
{
    // drawer bottom
    translate([-195,-129,80])
        %cube([290,255,5]);
    // drawer front
    translate([-220,-135,67.5])
        cube([320,5,27.5]);
    // drawer front L join
    translate([-195,-130,79])
        %union()
        {
            %cube([290,1,15]);
            %cube([290,15,1]);
        }
    // Handle
    translate([-220,-151,79])
        %difference()
        {
            cube([320,15,15]);
            translate([-1,1.5,-1.5])
            cube([322,12,15]);
        }
    // drawer back L
    translate([-195,126,79])
        %union()
        {
            cube([290,1,15]);
            translate([0,-14,0])
            cube([290,15,1]);
        }
}

for(j=[-125,-26])
for(i=[-199,-100,-1])
translate([i,j,117.5])
{
    color("green")
        cube([98,98,1.5]);
    for(k=[7:14:91])
    for(l=[7:14:91])
    // Led
    translate([k,l,-3])
    color("white")
    {
        sphere(r=1.5,$fn=100);
        cylinder(r=1.5,h=2.5,$fn=100);
        translate([0,0,2])
            cylinder(r=2,h=1,$fn=100);
    }
}




/*
translate([-200,-150,60])
    %cube([400,300,5]);
*/