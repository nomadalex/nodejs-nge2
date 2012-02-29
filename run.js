var nge2 = require('./build/Release/nge2');

console.log(nge2);

var app = new nge2.NgeApp();

var quit;

var red = nge2.CreateColor(255, 0, 0, 255, nge2.DISPLAY_PIXEL_FORMAT_8888);

console.log("red color : " + red);

app.init = function(){
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
  return 0;
}

app.mainloop = function(){
  try {
    nge2.InputProc();

    nge2.BeginScene(1);
    nge2.DrawLine(0, 0, 480, 272, red, nge2.DISPLAY_PIXEL_FORMAT_8888);
    nge2.EndScene();
  }
  catch (err) {
    console.log("err : " + err);
  }

  if (quit)
    return nge2.NGE_APP_QUIT;
  return nge2.NGE_APP_NORMAL;
}

app.fini = function(){
  nge2.Quit();
  return 0;
}

app.startRun();
