



<!DOCTYPE html>
<html>
<head>
 <link rel="icon" type="image/vnd.microsoft.icon" href="http://www.gstatic.com/codesite/ph/images/phosting.ico">
 
 <script type="text/javascript">
 
 
 
 var codesite_token = "da2833fc8ef1ff6102e2ca807cc50b7f";
 
 
 var logged_in_user_email = "laellin@gmail.com";
 
 
 var relative_base_url = "";
 
 </script>
 
 
 <title>rfm22b.c - 
 magicstuff-rpg -
 
 Project Hosting on Google Code</title>
 <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" >
 <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" >
 
 <meta name="ROBOTS" content="NOARCHIVE">
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/6191598954148986782/css/ph_core.css">
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/6191598954148986782/css/ph_detail.css" >
 
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/6191598954148986782/css/d_sb_20080522.css" >
 
 
 
<!--[if IE]>
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/6191598954148986782/css/d_ie.css" >
<![endif]-->
 <style type="text/css">
 .menuIcon.off { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -42px }
 .menuIcon.on { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -28px }
 .menuIcon.down { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 0; }
 
 
 
  tr.inline_comment {
 background: #fff;
 vertical-align: top;
 }
 div.draft, div.published {
 padding: .3em;
 border: 1px solid #999; 
 margin-bottom: .1em;
 font-family: arial, sans-serif;
 max-width: 60em;
 }
 div.draft {
 background: #ffa;
 } 
 div.published {
 background: #e5ecf9;
 }
 div.published .body, div.draft .body {
 padding: .5em .1em .1em .1em;
 max-width: 60em;
 white-space: pre-wrap;
 white-space: -moz-pre-wrap;
 white-space: -pre-wrap;
 white-space: -o-pre-wrap;
 word-wrap: break-word;
 font-size: 1em;
 }
 div.draft .actions {
 margin-left: 1em;
 font-size: 90%;
 }
 div.draft form {
 padding: .5em .5em .5em 0;
 }
 div.draft textarea, div.published textarea {
 width: 95%;
 height: 10em;
 font-family: arial, sans-serif;
 margin-bottom: .5em;
 }

 
 .nocursor, .nocursor td, .cursor_hidden, .cursor_hidden td {
 background-color: white;
 height: 2px;
 }
 .cursor, .cursor td {
 background-color: darkblue;
 height: 2px;
 display: '';
 }
 
 
.list {
 border: 1px solid white;
 margin-bottom:0;
}

 </style>
</head>
<body class="t4">
 <script type="text/javascript">
 var _gaq = _gaq || [];
 _gaq.push(
 ['siteTracker._setAccount', 'UA-18071-1'],
 ['siteTracker._trackPageview']);
 
 (function() {
 var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
 ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
 (document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(ga);
 })();
 </script>
<div class="headbg">
 <div id="gaia">
 
 <span>
 
 
 <b>laellin@gmail.com</b>
 
 
 | <a href="/u/laellin/" id="projects-dropdown" onclick="return false;"
 ><u>My favorites</u> <small>&#9660;</small></a>
 | <a href="/u/laellin/" onclick="_CS_click('/gb/ph/profile');" 
 title="Profile, Updates, and Settings"
 ><u>Profile</u></a>
 | <a href="https://www.google.com/accounts/Logout?continue=http%3A%2F%2Fcode.google.com%2Fp%2Fmagicstuff-rpg%2Fsource%2Fbrowse%2Ftrunk%2Frfm22%2Frf%2Frfm22b.c" 
 onclick="_CS_click('/gb/ph/signout');"
 ><u>Sign out</u></a>
 
 </span>

 </div>
 <div class="gbh" style="left: 0pt;"></div>
 <div class="gbh" style="right: 0pt;"></div>
 
 
 <div style="height: 1px"></div>
<!--[if lte IE 7]>
<div style="text-align:center;">
Your version of Internet Explorer is not supported. Try a browser that
contributes to open source, such as <a href="http://www.firefox.com">Firefox</a>,
<a href="http://www.google.com/chrome">Google Chrome</a>, or
<a href="http://code.google.com/chrome/chromeframe/">Google Chrome Frame</a>.
</div>
<![endif]-->




 <table style="padding:0px; margin: 0px 0px 10px 0px; width:100%" cellpadding="0" cellspacing="0">
 <tr style="height: 58px;">
 
 <td id="plogo">
 <a href="/p/magicstuff-rpg/">
 
 <img src="http://www.gstatic.com/codesite/ph/images/defaultlogo.png" alt="Logo">
 
 </a>
 </td>
 
 <td style="padding-left: 0.5em">
 
 <div id="pname">
 <a href="/p/magicstuff-rpg/">magicstuff-rpg</a>
 </div>
 <div id="psum">
 <a id="project_summary_link" href="/p/magicstuff-rpg/" >Software development for game communicator with ARM architecture</a>
 
 </div>
 
 </td>
 <td style="white-space:nowrap;text-align:right; vertical-align:bottom;">
 
 <form action="/hosting/search">
 <input size="30" name="q" value="" type="text">
 <input type="submit" name="projectsearch" value="Search projects" >
 </form>
 
 </tr>
 </table>

</div>

 
<div id="mt" class="gtb"> 
 <a href="/p/magicstuff-rpg/" class="tab ">Project&nbsp;Home</a> 
 
 
 
 
 <a href="/p/magicstuff-rpg/downloads/list" class="tab ">Downloads</a>
 
 
 
 
 
 <a href="/p/magicstuff-rpg/w/list" class="tab ">Wiki</a>
 
 
 
 
 
 <a href="/p/magicstuff-rpg/issues/list"
 class="tab ">Issues</a>
 
 
 
 
 
 <a href="/p/magicstuff-rpg/source/checkout"
 class="tab active">Source</a>
 
 
 
 <div class=gtbc></div>
</div>
<table cellspacing="0" cellpadding="0" width="100%" align="center" border="0" class="st">
 <tr>
 
 
 
 
 
 
 <td class="subt">
 <div class="st2">
 <div class="isf">
 
 
 
 <span class="inst1"><a href="/p/magicstuff-rpg/source/checkout">Checkout</a></span> &nbsp;
 <span class="inst2"><a href="/p/magicstuff-rpg/source/browse/">Browse</a></span> &nbsp;
 <span class="inst3"><a href="/p/magicstuff-rpg/source/list">Changes</a></span> &nbsp;
 
 <form action="http://www.google.com/codesearch" method="get" style="display:inline"
 onsubmit="document.getElementById('codesearchq').value = document.getElementById('origq').value + ' package:http://magicstuff-rpg\\.googlecode\\.com'">
 <input type="hidden" name="q" id="codesearchq" value="">
 <input type="text" maxlength="2048" size="38" id="origq" name="origq" value="" title="Google Code Search" style="font-size:92%">&nbsp;<input type="submit" value="Search Trunk" name="btnG" style="font-size:92%">
 
 
 
 </form>
 </div>
</div>

 </td>
 
 
 
 <td align="right" valign="top" class="bevel-right"></td>
 </tr>
</table>
<script type="text/javascript">
 var cancelBubble = false;
 function _go(url) { document.location = url; }
</script>


<div id="maincol"
 
>

 
<!-- IE -->




<div class="expand">
<div id="colcontrol">


<style type="text/css">
 #file_flipper { display: inline; float: right; white-space: nowrap; }
 #file_flipper.hidden { display: none; }
 #file_flipper .pagelink { color: #0000CC; text-decoration: underline; }
 #file_flipper #visiblefiles { padding-left: 0.5em; padding-right: 0.5em; }
</style>
<div id="nav_and_rev" class="heading">
 <div class="list">
 <div class="pagination" style="margin-left: 2em">
 <table cellpadding="0" cellspacing="0" class="flipper">
 <tbody>
 <tr>
 
 <td><b>r42</b></td>
 
 </tr>
 </tbody>
 </table>
 </div>
 
 <div class="" style="vertical-align: top">
 <div class="src_crumbs src_nav">
 <strong class="src_nav">Source path:&nbsp;</strong>
 <span id="crumb_root">
 
 <a href="/p/magicstuff-rpg/source/browse/">svn</a>/&nbsp;</span>
 <span id="crumb_links" class="ifClosed"><a href="/p/magicstuff-rpg/source/browse/trunk/">trunk</a><span class="sp">/&nbsp;</span><a href="/p/magicstuff-rpg/source/browse/trunk/rfm22/">rfm22</a><span class="sp">/&nbsp;</span><a href="/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/">rf</a><span class="sp">/&nbsp;</span>rfm22b.c</span>
 
 
 
 </div>
 
 </div>
 <div style="clear:both"></div>
 </div>
</div>


<div class="fc">
 
 
 
<style type="text/css">
.undermouse span {
 background-image: url(http://www.gstatic.com/codesite/ph/images/comments.gif); }
</style>
<table class="opened" id="review_comment_area"
><tr>
<td id="nums">
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
<pre><table width="100%" id="nums_table_0"><tr id="gr_svn42_1"

><td id="1"><a href="#1">1</a></td></tr
><tr id="gr_svn42_2"

><td id="2"><a href="#2">2</a></td></tr
><tr id="gr_svn42_3"

><td id="3"><a href="#3">3</a></td></tr
><tr id="gr_svn42_4"

><td id="4"><a href="#4">4</a></td></tr
><tr id="gr_svn42_5"

><td id="5"><a href="#5">5</a></td></tr
><tr id="gr_svn42_6"

><td id="6"><a href="#6">6</a></td></tr
><tr id="gr_svn42_7"

><td id="7"><a href="#7">7</a></td></tr
></table></pre>
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
</td>
<td id="lines">
<pre class="prettyprint"><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
<pre class="prettyprint lang-c"><table id="src_table_0"><tr
id=sl_svn42_1

><td class="source">/*<br></td></tr
><tr
id=sl_svn42_2

><td class="source"> * rfm22b.c<br></td></tr
><tr
id=sl_svn42_3

><td class="source"> *<br></td></tr
><tr
id=sl_svn42_4

><td class="source"> *  Created on: Sep 2, 2010<br></td></tr
><tr
id=sl_svn42_5

><td class="source"> *      Author: chai<br></td></tr
><tr
id=sl_svn42_6

><td class="source"> */<br></td></tr
><tr
id=sl_svn42_7

><td class="source"><br></td></tr
></table></pre>
<pre class="prettyprint"><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
</td>
</tr></table>
<script type="text/javascript">
 var lineNumUnderMouse = -1;
 
 function gutterOver(num) {
 gutterOut();
 var newTR = document.getElementById('gr_svn42_' + num);
 if (newTR) {
 newTR.className = 'undermouse';
 }
 lineNumUnderMouse = num;
 }
 function gutterOut() {
 if (lineNumUnderMouse != -1) {
 var oldTR = document.getElementById(
 'gr_svn42_' + lineNumUnderMouse);
 if (oldTR) {
 oldTR.className = '';
 }
 lineNumUnderMouse = -1;
 }
 }
 var numsGenState = {table_base_id: 'nums_table_'};
 var srcGenState = {table_base_id: 'src_table_'};
 var alignerRunning = false;
 var startOver = false;
 function setLineNumberHeights() {
 if (alignerRunning) {
 startOver = true;
 return;
 }
 numsGenState.chunk_id = 0;
 numsGenState.table = document.getElementById('nums_table_0');
 numsGenState.row_num = 0;
 srcGenState.chunk_id = 0;
 srcGenState.table = document.getElementById('src_table_0');
 srcGenState.row_num = 0;
 alignerRunning = true;
 continueToSetLineNumberHeights();
 }
 function rowGenerator(genState) {
 if (genState.row_num < genState.table.rows.length) {
 var currentRow = genState.table.rows[genState.row_num];
 genState.row_num++;
 return currentRow;
 }
 var newTable = document.getElementById(
 genState.table_base_id + (genState.chunk_id + 1));
 if (newTable) {
 genState.chunk_id++;
 genState.row_num = 0;
 genState.table = newTable;
 return genState.table.rows[0];
 }
 return null;
 }
 var MAX_ROWS_PER_PASS = 1000;
 function continueToSetLineNumberHeights() {
 var rowsInThisPass = 0;
 var numRow = 1;
 var srcRow = 1;
 while (numRow && srcRow && rowsInThisPass < MAX_ROWS_PER_PASS) {
 numRow = rowGenerator(numsGenState);
 srcRow = rowGenerator(srcGenState);
 rowsInThisPass++;
 if (numRow && srcRow) {
 if (numRow.offsetHeight != srcRow.offsetHeight) {
 numRow.firstChild.style.height = srcRow.offsetHeight + 'px';
 }
 }
 }
 if (rowsInThisPass >= MAX_ROWS_PER_PASS) {
 setTimeout(continueToSetLineNumberHeights, 10);
 } else {
 alignerRunning = false;
 if (startOver) {
 startOver = false;
 setTimeout(setLineNumberHeights, 500);
 }
 }
 }
 // Do 2 complete passes, because there can be races
 // between this code and prettify.
 startOver = true;
 setTimeout(setLineNumberHeights, 250);
 window.onresize = setLineNumberHeights;
</script>

 
 
 <div id="log">
 <div style="text-align:right">
 <a class="ifCollapse" href="#" onclick="_toggleMeta('', 'p', 'magicstuff-rpg', this)">Show details</a>
 <a class="ifExpand" href="#" onclick="_toggleMeta('', 'p', 'magicstuff-rpg', this)">Hide details</a>
 </div>
 <div class="ifExpand">
 
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="changelog">
 <p>Change log</p>
 <div>
 <a href="/p/magicstuff-rpg/source/detail?spec=svn42&r=39">r39</a>
 by chai.mail0
 on Dec 05, 2010
 &nbsp; <a href="/p/magicstuff-rpg/source/diff?spec=svn42&r=39&amp;format=side&amp;path=/trunk/rfm22/rf/rfm22b.c&amp;old_path=/trunk/rfm22/rf/rfm22b.c&amp;old=">Diff</a>
 </div>
 <pre>[No log message]</pre>
 </div>
 
 
 
 
 
 
 <script type="text/javascript">
 var detail_url = '/p/magicstuff-rpg/source/detail?r=39&spec=svn42';
 var publish_url = '/p/magicstuff-rpg/source/detail?r=39&spec=svn42#publish';
 // describe the paths of this revision in javascript.
 var changed_paths = [];
 var changed_urls = [];
 
 changed_paths.push('/trunk/rfm22/rf');
 changed_urls.push('/p/magicstuff-rpg/source/browse/trunk/rfm22/rf?r\x3d39\x26spec\x3dsvn42');
 
 
 changed_paths.push('/trunk/rfm22/rf/rfm22b.c');
 changed_urls.push('/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/rfm22b.c?r\x3d39\x26spec\x3dsvn42');
 
 var selected_path = '/trunk/rfm22/rf/rfm22b.c';
 
 
 changed_paths.push('/trunk/rfm22/rf/rfm22b.h');
 changed_urls.push('/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/rfm22b.h?r\x3d39\x26spec\x3dsvn42');
 
 
 changed_paths.push('/trunk/rfm22/rf/rfm22b_registermap.h');
 changed_urls.push('/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/rfm22b_registermap.h?r\x3d39\x26spec\x3dsvn42');
 
 
 changed_paths.push('/trunk/rfm22/rf/rfm_hw.c');
 changed_urls.push('/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/rfm_hw.c?r\x3d39\x26spec\x3dsvn42');
 
 
 changed_paths.push('/trunk/rfm22/rf/rfm_hw.h');
 changed_urls.push('/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/rfm_hw.h?r\x3d39\x26spec\x3dsvn42');
 
 
 changed_paths.push('/trunk/rfm22/rf/rfm_hwconfig.h');
 changed_urls.push('/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/rfm_hwconfig.h?r\x3d39\x26spec\x3dsvn42');
 
 
 changed_paths.push('/trunk/rfm22/rf/spi.c');
 changed_urls.push('/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/spi.c?r\x3d39\x26spec\x3dsvn42');
 
 
 changed_paths.push('/trunk/rfm22/rf/spi.h');
 changed_urls.push('/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/spi.h?r\x3d39\x26spec\x3dsvn42');
 
 
 function getCurrentPageIndex() {
 for (var i = 0; i < changed_paths.length; i++) {
 if (selected_path == changed_paths[i]) {
 return i;
 }
 }
 }
 function getNextPage() {
 var i = getCurrentPageIndex();
 if (i < changed_paths.length - 1) {
 return changed_urls[i + 1];
 }
 return null;
 }
 function getPreviousPage() {
 var i = getCurrentPageIndex();
 if (i > 0) {
 return changed_urls[i - 1];
 }
 return null;
 }
 function gotoNextPage() {
 var page = getNextPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoPreviousPage() {
 var page = getPreviousPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoDetailPage() {
 window.location = detail_url;
 }
 function gotoPublishPage() {
 window.location = publish_url;
 }
</script>

 
 <style type="text/css">
 #review_nav {
 border-top: 3px solid white;
 padding-top: 6px;
 margin-top: 1em;
 }
 #review_nav td {
 vertical-align: middle;
 }
 #review_nav select {
 margin: .5em 0;
 }
 </style>
 <div id="review_nav">
 <table><tr><td>Go to:&nbsp;</td><td>
 <select name="files_in_rev" onchange="window.location=this.value">
 
 <option value="/p/magicstuff-rpg/source/browse/trunk/rfm22/rf?r=39&amp;spec=svn42"
 
 >/trunk/rfm22/rf</option>
 
 <option value="/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/rfm22b.c?r=39&amp;spec=svn42"
 selected="selected"
 >/trunk/rfm22/rf/rfm22b.c</option>
 
 <option value="/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/rfm22b.h?r=39&amp;spec=svn42"
 
 >/trunk/rfm22/rf/rfm22b.h</option>
 
 <option value="/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/rfm22b_registermap.h?r=39&amp;spec=svn42"
 
 >...nk/rfm22/rf/rfm22b_registermap.h</option>
 
 <option value="/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/rfm_hw.c?r=39&amp;spec=svn42"
 
 >/trunk/rfm22/rf/rfm_hw.c</option>
 
 <option value="/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/rfm_hw.h?r=39&amp;spec=svn42"
 
 >/trunk/rfm22/rf/rfm_hw.h</option>
 
 <option value="/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/rfm_hwconfig.h?r=39&amp;spec=svn42"
 
 >/trunk/rfm22/rf/rfm_hwconfig.h</option>
 
 <option value="/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/spi.c?r=39&amp;spec=svn42"
 
 >/trunk/rfm22/rf/spi.c</option>
 
 <option value="/p/magicstuff-rpg/source/browse/trunk/rfm22/rf/spi.h?r=39&amp;spec=svn42"
 
 >/trunk/rfm22/rf/spi.h</option>
 
 </select>
 </td></tr></table>
 
 
 



 
 </div>
 
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="older_bubble">
 <p>Older revisions</p>
 
 <a href="/p/magicstuff-rpg/source/list?path=/trunk/rfm22/rf/rfm22b.c&start=39">All revisions of this file</a>
 </div>
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="fileinfo_bubble">
 <p>File info</p>
 
 <div>Size: 72 bytes,
 7 lines</div>
 
 <div><a href="http://magicstuff-rpg.googlecode.com/svn/trunk/rfm22/rf/rfm22b.c">View raw file</a></div>
 </div>
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 </div>
 </div>


</div>
</div>
</div>

<script src="http://www.gstatic.com/codesite/ph/6191598954148986782/js/prettify/prettify.js"></script>
<script type="text/javascript">prettyPrint();</script>


<script src="http://www.gstatic.com/codesite/ph/6191598954148986782/js/source_file_scripts.js"></script>

 <script type="text/javascript" src="http://kibbles.googlecode.com/files/kibbles-1.3.1.comp.js"></script>
 <script type="text/javascript">
 var lastStop = null;
 var initilized = false;
 
 function updateCursor(next, prev) {
 if (prev && prev.element) {
 prev.element.className = 'cursor_stop cursor_hidden';
 }
 if (next && next.element) {
 next.element.className = 'cursor_stop cursor';
 lastStop = next.index;
 }
 }
 
 function pubRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initilized) {
 reloadCursors();
 }
 }
 
 function draftRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initilized) {
 reloadCursors();
 }
 }
 
 function draftDestroyed(data) {
 updateCursorForCell(data.cellId, 'nocursor');
 if (initilized) {
 reloadCursors();
 }
 }
 function reloadCursors() {
 kibbles.skipper.reset();
 loadCursors();
 if (lastStop != null) {
 kibbles.skipper.setCurrentStop(lastStop);
 }
 }
 // possibly the simplest way to insert any newly added comments
 // is to update the class of the corresponding cursor row,
 // then refresh the entire list of rows.
 function updateCursorForCell(cellId, className) {
 var cell = document.getElementById(cellId);
 // we have to go two rows back to find the cursor location
 var row = getPreviousElement(cell.parentNode);
 row.className = className;
 }
 // returns the previous element, ignores text nodes.
 function getPreviousElement(e) {
 var element = e.previousSibling;
 if (element.nodeType == 3) {
 element = element.previousSibling;
 }
 if (element && element.tagName) {
 return element;
 }
 }
 function loadCursors() {
 // register our elements with skipper
 var elements = CR_getElements('*', 'cursor_stop');
 var len = elements.length;
 for (var i = 0; i < len; i++) {
 var element = elements[i]; 
 element.className = 'cursor_stop cursor_hidden';
 kibbles.skipper.append(element);
 }
 }
 function toggleComments() {
 CR_toggleCommentDisplay();
 reloadCursors();
 }
 function keysOnLoadHandler() {
 // setup skipper
 kibbles.skipper.addStopListener(
 kibbles.skipper.LISTENER_TYPE.PRE, updateCursor);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_top', 50);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_bottom', 100);
 // Register our keys
 kibbles.skipper.addFwdKey("n");
 kibbles.skipper.addRevKey("p");
 kibbles.keys.addKeyPressListener(
 'u', function() { window.location = detail_url; });
 kibbles.keys.addKeyPressListener(
 'r', function() { window.location = detail_url + '#publish'; });
 
 kibbles.keys.addKeyPressListener('j', gotoNextPage);
 kibbles.keys.addKeyPressListener('k', gotoPreviousPage);
 
 
 }
 </script>
<script src="http://www.gstatic.com/codesite/ph/6191598954148986782/js/code_review_scripts.js"></script>
<script type="text/javascript">
 
 // the comment form template
 var form = '<div class="draft"><div class="header"><span class="title">Draft comment:</span></div>' +
 '<div class="body"><form onsubmit="return false;"><textarea id="$ID">$BODY</textarea><br>$ACTIONS</form></div>' +
 '</div>';
 // the comment "plate" template used for both draft and published comment "plates".
 var draft_comment = '<div class="draft" ondblclick="$ONDBLCLICK">' +
 '<div class="header"><span class="title">Draft comment:</span><span class="actions">$ACTIONS</span></div>' +
 '<pre id="$ID" class="body">$BODY</pre>' +
 '</div>';
 var published_comment = '<div class="published">' +
 '<div class="header"><span class="title"><a href="$PROFILE_URL">$AUTHOR:</a></span><div>' +
 '<pre id="$ID" class="body">$BODY</pre>' +
 '</div>';

 function showPublishInstructions() {
 var element = document.getElementById('review_instr');
 if (element) {
 element.className = 'opened';
 }
 }
 function revsOnLoadHandler() {
 // register our source container with the commenting code
 var paths = {'svn42': '/trunk/rfm22/rf/rfm22b.c'}
 CR_setup('', 'p', 'magicstuff-rpg', '', 'svn42', paths,
 'da2833fc8ef1ff6102e2ca807cc50b7f', CR_BrowseIntegrationFactory);
 // register our hidden ui elements with the code commenting code ui builder.
 CR_registerLayoutElement('form', form);
 CR_registerLayoutElement('draft_comment', draft_comment);
 CR_registerLayoutElement('published_comment', published_comment);
 
 CR_registerActivityListener(CR_ACTIVITY_TYPE.REVEAL_DRAFT_PLATE, showPublishInstructions);
 
 CR_registerActivityListener(CR_ACTIVITY_TYPE.REVEAL_PUB_PLATE, pubRevealed);
 CR_registerActivityListener(CR_ACTIVITY_TYPE.REVEAL_DRAFT_PLATE, draftRevealed);
 CR_registerActivityListener(CR_ACTIVITY_TYPE.DISCARD_DRAFT_COMMENT, draftDestroyed);
 
 
 
 
 
 
 
 var initilized = true;
 reloadCursors();
 }
 window.onload = function() {keysOnLoadHandler(); revsOnLoadHandler();};

</script>
<script type="text/javascript" src="http://www.gstatic.com/codesite/ph/6191598954148986782/js/dit_scripts.js"></script>

 
 
 <script type="text/javascript" src="http://www.gstatic.com/codesite/ph/6191598954148986782/js/core_scripts_20081103.js"></script>
 <script type="text/javascript" src="/js/codesite_product_dictionary_ph.pack.04102009.js"></script>
 </div>
<div id="footer" dir="ltr">
 
 <div class="text">
 
 &copy;2010 Google -
 <a href="/projecthosting/terms.html">Terms</a> -
 <a href="http://www.google.com/privacy.html">Privacy</a> -
 <a href="/p/support/">Project Hosting Help</a>
 
 </div>
</div>

 <div class="hostedBy" style="margin-top: -20px;">
 <span style="vertical-align: top;">Powered by <a href="http://code.google.com/projecthosting/">Google Project Hosting</a></span>
 </div>
 
 


 
 </body>
</html>

