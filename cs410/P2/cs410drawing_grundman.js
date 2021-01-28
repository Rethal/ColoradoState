var   gcx  = 1; 
var   gcy  = 0.50;
var theta  = 0.0;
var rotdel = 1.0/360.0;

function drawIt() {
	dboard = document.getElementById("dboard");
	cntxt  = dboard.getContext('2d');
	w = dboard.width;
	h = dboard.height;
	clearIt();
	cntxt.save();
	cntxt.setTransform(h, 0.0, 0.0, -h, 0.0, h);
	cntxt.lineWidth=0.01; 
	cntxt.rect(0.2,0.2,1.0,0.6);
	cntxt.stroke();
	drawEllipse();
	drawArc();
	drawArc2();
	cntxt.restore();
	drawRect("LightBlue","DarkBlue",.05,.1,.01,.02);
	drawRect("LightBlue","DarkBlue",0,0,.01,.02);
	drawRect("LightBlue","DarkBlue",1.49,.98,.01,.02);
	drawRect("Pink","DarkRed",.05,.025,.03,.0125);
	drawRect("Pink","DarkRed",.5,.25,.03,.0125);
	drawRect("Pink","DarkRed",.95,.025,.03,.0125);
	drawRect("Pink","DarkRed",1.3,.25,.03,.0125);
	drawRect("Pink","DarkRed",1.2,.95,.03,.0125);
	drawStar();
	drawPoly(gcx,gcy,theta);
	theta = theta + (rotdel * 2.0 * Math.PI);
	setTimeout(drawIt, 30);
}

function drawRect(fill, line, cx, cy,x,y){
	cntxt.save();
	cntxt.transform(h, 0.0, 0.0, -h, 0.0, h);
	cntxt.lineWidth=0.005; 
	cntxt.fillStyle   = fill;
	cntxt.strokeStyle = line;
	cntxt.beginPath();
	cntxt.rect(cx,cy,x,y);
	cntxt.fill();
	cntxt.stroke();
	cntxt.restore();
}

function drawEllipse(){
	cntxt.save();
	cntxt.transform(1.5,0,0,1,.5,.33);
	cntxt.fillStyle = "Black";
	cntxt.strokeStyle = "White";
	cntxt.beginPath();
	cntxt.arc(.1,0,.05,0,2*Math.PI)
	cntxt.fill();
	cntxt.stroke();
	cntxt.restore();
}

function drawArc(){
	cntxt.save();
	cntxt.transform(1,0,0,1,.5,.5);
	cntxt.fillStyle = "Blue";
	cntxt.strokeStyle = "Gray";
	cntxt.beginPath();
	cntxt.arc(.1,.1,.05,-Math.PI/2,Math.PI)
	cntxt.fill();
	cntxt.stroke();
	cntxt.restore();
}
function drawArc2(){
	cntxt.save();
	cntxt.transform(1.5,0,0,1,.5,.5);
	cntxt.fillStyle = "Maroon";
	cntxt.strokeStyle = "ForestGreen";
	cntxt.beginPath();
	cntxt.arc(.15,.0125,.05,0,Math.PI)
	cntxt.fill();
	cntxt.stroke();
	cntxt.restore();
}
function drawStar(cx,cy,theta){
	cntxt.save();
	cntxt.transform(1.5, 0.0, 0.0, 1.0, cx, cy);
	cntxt.rotate(theta * 2.0 * Math.PI);
	cntxt.fillStyle   = "Yellow";
	cntxt.strokeStyle = "Orange"; 
	cntxt.beginPath();
    	cntxt.moveTo(25,   50);
    	cntxt.lineTo(75, 50);
    	cntxt.lineTo(25, 100);
    	cntxt.lineTo(50,  25);
	cntxt.lineTo(75, 100);
	cntxt.lineTo(25,50);   
    	cntxt.closePath();
    	cntxt.fill();
    	cntxt.stroke();
	cntxt.restore();
}
function drawPoly(cx,cy,theta){
	cntxt.save();
	cntxt.transform(1.0, 0.0, 0.0, 1.0, cx, cy);
	cntxt.rotate(theta * 2.0 * Math.PI);
	cntxt.strokeStyle = "Purple";
	cntxt.beginPath();
	cntxt.moveTo(150,50);
	cntxt.lineTo(150,75);
	cntxt.lineTo(160,90);
	cntxt.lineTo(170,75);
	cntxt.lineTo(170,50);
	cntxt.lineTo(150,50);
	cntxt.closePath();
	cntxt.stroke();
	cntxt.restore();
}

function clearIt() {
	cntxt.save();
	cntxt.setTransform(1, 0, 0, 1, 0, 0);
	cntxt.clearRect(0, 0, dboard.width, dboard.height);
	cntxt.restore();	
}
function init() {
	drawIt();
}
