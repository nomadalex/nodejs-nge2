var nge2 = require('./build/Release/node_nge2');

var app = new nge2.NgeApp();

var quit
  , dtype = nge2.DISPLAY_PIXEL_FORMAT_8888
  , red = nge2.CreateColor(255, 0, 0, 255, dtype)
  , yellow = nge2.CreateColor(255, 255, 0, 255, dtype)
  , blue = nge2.CreateColor(0, 255, 255, 255, dtype);

var img, bg, logo;

app.init = function(end){
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

  img = nge2.Image.createEx(10, 10, red, dtype);
  bg = nge2.Image.load("images/demo0.jpg", dtype, 1);
  if (!bg)
    console.log("can not find demo0.jpg!");

  logo = nge2.Image.load("images/nge2logo.png", nge2.DISPLAY_PIXEL_FORMAT_4444, 1);
  if (!logo)
    console.log("can not find nge2logo.png!");

  end();
}

app.mainloop = function(end){
  try {
    nge2.InputProc();

    nge2.BeginScene(1);
    bg.draw(0,0,0,0, 0,0, 480, 272);
    logo.draw(0,0,0,0, 128,0,256,256);
    img.draw(0,0,0,0, 100,0,0,0);
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
