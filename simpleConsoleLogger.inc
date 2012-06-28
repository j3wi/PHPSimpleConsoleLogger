<?php 
include 'logger/simpleConsoleLoggerConstants.inc';

define('SKIP_VALUE_FOR_CLASS_OR_FUNCTIONS', 3);
define('SKIP_VALUE_FOR_FILE_OR_LINE', 2);

function logger($message) {
	logIfLogEnabled($message);
}

function logIfLogEnabled($message) {
	if (LOG_ENABLED){
		$correctedMessage = correctMessage($message);
		$messageWithInfo = prefixCallerInfo($correctedMessage);
		writeJSLogger(addslashes($messageWithInfo));
	}
}

function correctMessage($message) {
	if (is_string($message)) {
		$message = addslashes($message);
	} else {
		$message = expandArrayAndTakeAwayNewLines($message);
	}
	return $message;
}

function expandArrayAndTakeAwayNewLines($array) {
	$array = print_r($array, true);
	$array = str_replace("\n",'',$array);
	return $array;
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
	try {
		return tryGetFunction($trace);
	} catch (Exception $e) {
		return "";
	}
}
function tryGetFunction($trace) {
	$caller = skipLoggerCallsFromTraceForClassAndFunction($trace);

	$function = $caller['function'];
	if ($caller['function'] == "include") {
		$function = "";
	}
	return $function;
}

function getClass($trace) {
	try {
		return tryGetClass($trace);
	} catch (Exception $e) {
		return "";
	}
}

function tryGetClass($trace) {
	$caller = skipLoggerCallsFromTraceForClassAndFunction($trace);
	$class = "";
	if (isset($caller['class'])){
		$class = $caller['class'];
	}
	return $class;
}

function skipLoggerCallsFromTraceForClassAndFunction($trace) {
	$caller = $trace[SKIP_VALUE_FOR_CLASS_OR_FUNCTIONS];
	if (!isset($caller)){
		throw new Exception("Not function Caller");
	}
	
	return $caller;
}

function skipLoggerCallsFromTraceForFileAndLine($trace) {
	$caller = $trace[SKIP_VALUE_FOR_FILE_OR_LINE];
	return $caller;
}

function formatMessage($file, $line, $class, $function, $message) {
	$newmessage = "[$file:$line]$class->$function()=>$message";

	return $newmessage;
}
?>