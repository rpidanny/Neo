
const char INDEX[] PROGMEM = R"=====(
<!Doctype html>
<html>
<head>
  <link href='https://fonts.googleapis.com/css?family=Roboto+Mono:400,500' rel='stylesheet' type='text/css'>
  <meta charset='utf-8'>
  <meta name='viewport' content='width=device-width, initial-scale=0.8, minimal-ui'>
  <meta name='description' content='Dot Matrix Editor'>
  <meta name='author' content='rpidanny - Abhishek Maharjan'>
  <meta name='theme-color' content='#36393E' />
  <title>Dot Matrix Editor</title>
  <link rel='stylesheet' href='css/style.css'>
  <script src='js/app.js'></script>
</head>
<body onload='onLoad()'>
  <nav>
    <div class='container'>
      <div class='navbar-header'>
        Dot Matrix Editor
      </div>
    </div>
  </nav>
  <div class='container'>
    <div class='row'>
      <div class='col-12'>
        <div id='_grid' oncontextmenu='return false;'></div>
      </div>
    </div>
    <div class='row'>
      <div class='col-12'>
        <div class='btn-group'>
          <button type='button' class='btn btn-default' id='generateButton'>Update</button>
        </div>
        <div class='btn-group'>
          <button type='button' class='btn btn-default' id='clearButton'>Clear</button>
        </div>
      </div>
    </div>
    <div class='row'>
      <div class='col-12'>
        <footer class='footer'>
          <p class='text-muted'>Created By
            <a href='http://rpidanny.github.io'>Abhishek Maharjan</a>,
            <a href='https://instagram.com/rpidanny'>@rpidanny</a>. Source at
            <a href='https://github.com/rpidanny/Neo'>GitHub</a>
          </p>
        </footer>
      </div>
    </div>
  </div>
</body>
</html>
)=====";