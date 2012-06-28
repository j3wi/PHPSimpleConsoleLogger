PHPSimpleConsoleLogger
======================
Introduction
--------------
It's a simple console logger for PHP.

It uses the javascript console.log instruction to show the log messages.

You can access to those messages with the developer mode in Chrome or with Firebug for Firefox.

Use
----
You only need to include the *simpleConsoleLogger.inc* file and then call::

    logger("message");

Configuration
---------------
It's quite simple, no log levels, no files, ... you only can configure if enable or not the logs in the *simpleConsoleLoggerConstants.inc* by changing true to false in::

    define('LOG_ENABLED', true);

Format
--------
The format we use in this logger is: [**file**:**line**]**class**->**function**()=>**message**

It's defined in the **formatMessage** function if you want to change it::

    function formatMessage($file, $line, $class, $function, $message) {
        $newmessage = "[$file:$line]$class->$function()=>$message";
        return $newmessage;	
    }


Example:
-----------
If we call directly from a file::

    logger("Validating user: foobar")

the exit could be similar to::

    [functions.php:35]->validUser()=>Validating user: foobar



If the logger call is from a class method:

	logger("Create NoticesManager");

the exit will be similar to:

    [noticesManagerImp.php:9]NoticesManagerImp->__construct()=>Created NoticesManager


We can also call the logger with an Array, for example:

    logger($_POST);

will produce for example:

    [functions.php:5]->checkRedirect()=>Array(    [user] => foobar    [password] => 1234    [submit] => Acept) 