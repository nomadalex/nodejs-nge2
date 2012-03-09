var nge2 = require('./build/Release/node_nge2');

var app = new nge2.NgeApp();

var quit;

var bg, text_img, maskbox
  , box, icon = [];

function MAKE_RGBA_4444(r,g,b,a) {
  return nge2.CreateColor(r,g,b,a, nge2.DISPLAY_PIXEL_FORMAT_4444);
}
function MAKE_RGBA_8888(r,g,b,a) {
  return nge2.CreateColor(r,g,b,a, nge2.DISPLAY_PIXEL_FORMAT_8888);
}
function MAKE_RGB(r,g,b) {
  return nge2.CreateColor(r,g,b,255, nge2.DISPLAY_PIXEL_FORMAT_8888);
}

app.init = function(end){
  nge2.Init(nge2.INIT_VIDEO);
  nge2.InitInput(function(key) {
                   if (key == nge2.PSP_BUTTON_UP)
                     quit = true;
                 },
                 function(key) {
                   console.log(key);
                 }, 0);

  nge2.SetFontEncoding(nge2.NGE_ENCODING_UTF_8);
  nge2.SetScreenColor(255,255,255,255);

  bg = nge2.image_load("res/images/demo2_bg.jpg", nge2.DISPLAY_PIXEL_FORMAT_8888, 1);
  if (!bg)
    console.log("can not find demo2_bg.jpg!");

  box = nge2.image_load("res/images/demo2_box.jpg",nge2.DISPLAY_PIXEL_FORMAT_8888,1);
  if (!box)
    console.log("can not find demo2_box.jpg!");
  maskbox = MAKE_RGBA_8888(255,255,255,128);

  icon[0] = nge2.image_load_colorkey("res/images/demo2_icon1.png",nge2.DISPLAY_PIXEL_FORMAT_8888,MAKE_RGB(0,0,0),1);
  icon[1] = nge2.image_load_colorkey("res/images/demo2_icon0.bmp",nge2.DISPLAY_PIXEL_FORMAT_8888,MAKE_RGB(0,0,0),1);

  text_img = nge2.image_create(512, 512, nge2.DISPLAY_PIXEL_FORMAT_4444);

  var pf = [];

  var str1 = ["【报幕员】","下面播放的是由雪莉演唱的射手座。","欢迎大家收听！"]
    , str2 = ["【雪莉粉丝】","哇哇哇。。。太棒了！","XXXX女王SAMA，我爱你。"]
    , buf;

  pf[0] = nge2.create_font_hzk("res/fonts/GBK14", "res/fonts/ASC14", 14, nge2.DISPLAY_PIXEL_FORMAT_4444);
  nge2.font_setcolor(pf[0], MAKE_RGBA_4444(128,0,0,255));

  nge2.font_drawtext(pf[0], str2[0],text_img,100,195,nge2.FONT_SHOW_NORMAL);

  nge2.font_setcolor(pf[0], MAKE_RGBA_4444(255,0,0,255));
  for (var i = 1; i<3; i++) {
    nge2.font_drawtext(pf[0],str2[i],text_img,120,200+i*20,nge2.FONT_SHOW_SHADOW);
  }

  pf[1] = nge2.create_font_freetype("res/fonts/simfang.ttf", 13, nge2.DISPLAY_PIXEL_FORMAT_4444);
  nge2.font_setcolor(pf[1],MAKE_RGBA_4444(128,0,0,255));
  nge2.font_drawtext(pf[1],str1[0],text_img,100,30,nge2.FONT_SHOW_NORMAL);
  nge2.font_setcolor(pf[1],MAKE_RGBA_4444(255,0,0,255));
  for(var i =1;i<3;i++){
    nge2.font_drawtext(pf[1],str1[i],text_img,120,35+i*20,nge2.FONT_SHOW_NORMAL);
  }

  end();
}

app.mainloop = function(end){
  try {
    nge2.InputProc();

    nge2.BeginScene(1);
	nge2.ImageToScreen(bg,0,0);

	nge2.RenderQuad(box,0,0,0,0,70,185,1,1,0,maskbox);
	nge2.RenderQuad(box,0,0,0,0,70,5,1,1,0,maskbox);
	nge2.DrawImage(icon[0],0,0,0,0,-20,-37,128,128);
	nge2.DrawImage(icon[1],0,0,0,0,-20,143,128,128);
	nge2.ImageToScreen(text_img,0,0);
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
