var nge2 = require('./build/Release/node_nge2');

console.log("--------------");
console.log(nge2);
console.log("--------------");

var app = new nge2.NgeApp();

var quit;

var dtype = nge2.DISPLAY_PIXEL_FORMAT_8888
  , red = nge2.CreateColor(255, 0, 0, 255, dtype)
  , yellow = nge2.CreateColor(255, 255, 0, 255, dtype)
  , blue = nge2.CreateColor(0, 255, 255, 255, dtype);

console.log("red color : " + red);

app.init = function(end){
  console.log("current app : " + nge2.NgeApp.getCurrent());
  nge2.Init(nge2.INIT_VIDEO);
  nge2.InitInput(function(key) {
                   console.log(key);
                 },
                 function(key) {
                   console.log(key);
                   if (key == nge2.PSP_BUTTON_UP)
                     quit = true;
                 }, 0);
  nge2.SetScreenColor(255,255,255,255);

  end();
}

var polygons_x1 = [ 200.0, 300.0, 400.0, 300.0 ]
  , polygons_y1 = [ 10.0, 10.0, 70.0, 70.0 ]
  , polygons_x2 = [ 200.0, 300.0, 400.0 ]
  , polygons_y2 = [ 80.0, 80.0, 160.0 ]
  , polygons_x3 = [ 400.0, 450.0, 350.0 ]
  , polygons_y3 = [ 160.0, 250.0, 250.0 ]
  , polygons_colors = [ red, yellow, blue ];

app.mainloop = function(end){
  try {
    nge2.InputProc();
    // nge2.ShowFps(); // can not print

    nge2.BeginScene(1);
    nge2.DrawLine(0, 0, 480, 272, red, dtype);
    nge2.DrawRect(20,20,200,200,red,dtype);
    nge2.FillRect(40,40,100,100,red,dtype);
	nge2.DrawCircle(100,100,20,blue,dtype);
	nge2.FillCircle(150,150,20,yellow,dtype);
	nge2.DrawEllipse(200,200,20,40,blue,dtype);
	nge2.FillEllipse(250,250,40,20,yellow,dtype);
	nge2.DrawPolygon(polygons_x1,polygons_y1,4,blue,dtype);
    nge2.FillPolygon(polygons_x2,polygons_y2,3,red,dtype);
    nge2.FillPolygonGrad(polygons_x3,polygons_y3,3,polygons_colors, dtype);
    nge2.EndScene();
  }
  catch (err) {
    console.log("err : " + err);
    end(nge2.NGE_APP_QUIT);
    return;
  }

  if (quit)
    end(nge2.NGE_APP_QUIT);
  else
    end(nge2.NGE_APP_NORMAL);
}

app.fini = function(end){
  nge2.Quit();
  end();
}

app.startRun();
