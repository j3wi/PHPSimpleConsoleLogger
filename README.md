PHPSimpleConsoleLogger
======================
Introduction
--------------
It's a simple console logger for PHP.

It uses the javascript console.log instruction to show the log messages.

You can access to those messages with the developer mode in Chrome or with Firebug for Firefox.

Use
----
You only need to include the *simpleConsoleLogger.inc* file and then call:
   logger("message");

Configuration
---------------
It's quite simple, no log levels, no files, ... you only can configure if enable or not the logs in the *simpleConsoleLoggerConstants.inc* by changing true to false in ::
   define('LOG_ENABLED', true);
