<?php 
include 'logger/simpleConsoleLoggerConstants.inc';

function logger($message) {
	if (LOG_ENABLED){
		$messageWithInfo = prefixCallerInfo($message);
		writeJSLogger($messageWithInfo);
	}
}

function writeJSLogger($message){
	echo "<script type=\"text/javascript\">";
	echo "console.log(\"".$message."\")";
	echo "</script>\n";
}

function prefixCallerInfo($message){
	$trace = debug_backtrace();
	$file = getFile($trace);
	$line = getLine($trace);
	$class = getClass($trace);
	$function = getFunction($trace);
	
	return formatMessage($file, $line, $class, $function, $message);
}

function getFile($trace) {
	$caller = skipLoggerCallsFromTraceForFileAndLine($trace);
	$splitedFilename = explode("\\", $caller['file']);
	$filename = $splitedFilename[sizeof($splitedFilename)-1];
	return $filename;
}

function getLine($trace) {
	$caller = skipLoggerCallsFromTraceForFileAndLine($trace);
	
	return $caller['line'];
}

function getFunction($trace) {
	$caller = skipLoggerCallsFromTraceForClassAndFunction($trace);

	$function = $caller['function'];
	if ($caller['function'] == "include") {
		$function = "";
	}
	return $function;
}

function getClass($trace) {
	$caller = skipLoggerCallsFromTraceForClassAndFunction($trace);
	$class = "";
	if (isset($caller['class'])){
		$class = $caller['class'];
	}
	return $class;
}

function skipLoggerCallsFromTraceForClassAndFunction($trace) {
	$caller = $trace[2];
	return $caller;
}

function skipLoggerCallsFromTraceForFileAndLine($trace) {
	$caller = $trace[1];
	return $caller;
}

function formatMessage($file, $line, $class, $function, $message) {
	$newmessage = "[$file:$line]$class->$function()=>$message";
	
	return $newmessage;	
}
?>