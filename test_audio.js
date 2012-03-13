var nge2 = require('./build/Release/node_nge2');

var app = new nge2.NgeApp();

var quit
  , dtype = nge2.DISPLAY_PIXEL_FORMAT_8888
  , red = nge2.CreateColor(255, 0, 0, 255, dtype)
  , yellow = nge2.CreateColor(255, 255, 0, 255, dtype)
  , blue = nge2.CreateColor(0, 255, 255, 255, dtype);

var bg, logo
  , audios = []
  , logomask1
  , logomask2;

app.init = function(end){
  nge2.Init(nge2.INIT_ALL);
  nge2.InitInput(function(key) {
                   if (key == nge2.PSP_BUTTON_UP)
                     quit = true;
                   if (key == nge2.PSP_BUTTON_CIRCLE) {
                     if (nge2.audioIsEof(audios[1]) == 1) {
                       nge2.audioRewind(audios[1]);
                       nge2.audioPlay(audios[1], 1, 0)
                     }
                   }
                 },
                 function(key) {
                   console.log(key);
                 }, 0);

  nge2.SetScreenColor(255,255,255,255);

  bg = nge2.image_load("res/images/demo0.jpg", dtype, 1);
  if (!bg)
    console.log("can not find demo0.jpg!");

  logo = nge2.image_load("res/images/nge2logo.png", nge2.DISPLAY_PIXEL_FORMAT_4444, 1);
  if (!logo)
    console.log("can not find nge2logo.png!");

  logomask1 = nge2.CreateColor(255,255,255,128, logo.dtype);
  logomask2 = nge2.CreateColor(100,100,100,255, logo.dtype);;

  audios[0] = nge2.CreateMp3Player();
  console.log(audios[0]);
  nge2.audioLoad(audios[0], "res/music/simple1.mp3");

  audios[1] = nge2.CreateWavPlayer();
  nge2.audioLoad(audios[1], "res/music/simple3.wav");

  audios[2] = nge2.CreateOggPlayer();
  nge2.audioLoad(audios[2], "res/music/test.ogg");

  nge2.audioPlay(audios[0], 1, 0);

  console.log("mp3 comes mix with ogg ~\n");
  nge2.audioPlay(audios[2], 1, 0);

  console.log("wav comes mix all~ \n");
  nge2.audioPlay(audios[1], 1, 0);

  end();
}

app.mainloop = function(end){
  try {
    nge2.InputProc();

    nge2.BeginScene(1);
    nge2.ImageToScreen(bg, 0,0);
    nge2.DrawImage(logo, 0,0,0,0, 128,0,256,256);
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
