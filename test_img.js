var nge2 = require('./build/Release/node_nge2');

var app = new nge2.NgeApp();

var quit
  , dtype = nge2.DISPLAY_PIXEL_FORMAT_8888
  , red = nge2.CreateColor(255, 0, 0, 255, dtype)
  , yellow = nge2.CreateColor(255, 255, 0, 255, dtype)
  , blue = nge2.CreateColor(0, 255, 255, 255, dtype);

var img, bg, logo
  , logomask1 = nge2.CreateColor(255,255,255,128, nge2.DISPLAY_PIXEL_FORMAT_4444)
  , logomask2 = nge2.CreateColor(100,100,100,255, nge2.DISPLAY_PIXEL_FORMAT_4444);

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

  img = nge2.image_create_ex(10, 10, red, dtype);
  bg = nge2.image_load("images/demo0.jpg", dtype, 1);
  if (!bg)
    console.log("can not find demo0.jpg!");

  logo = nge2.image_load("images/nge2logo.png", nge2.DISPLAY_PIXEL_FORMAT_4444, 1);
  if (!logo)
    console.log("can not find nge2logo.png!");

  end();
}

app.mainloop = function(end){
  try {
    nge2.InputProc();

    nge2.BeginScene(1);
    nge2.ImageToScreen(bg, 0,0);
    nge2.DrawImage(logo, 0,0,0,0, 128,0,256,256);
    nge2.DrawImage(img, 0,0,0,0, 100,0,0,0);
    nge2.DrawImageMask(logo, 0,0,0,0, 0,0,128,128, logomask1);
    nge2.DrawImageMask(logo, 0,0,0,0, 0,272-128,128,128, logomask2);
    nge2.DrawImageMask(logo, 0,0,0,0, 480-128,0,128,128, logomask2);
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
