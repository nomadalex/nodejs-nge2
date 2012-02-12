var nge2 = require('./build/Release/nge2');

console.log(nge2);

var app = new nge2.NgeApp();

var quit;

app.init = function(){
  console.log(nge2.NgeApp.getCurrent());
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
  nge2.InputProc();

  if (quit)
    return nge2.NGE_APP_QUIT;
  return nge2.NGE_APP_NORMAL;
}

app.fini = function(){
  nge2.Quit();
  return 0;
}

app.startRun();
