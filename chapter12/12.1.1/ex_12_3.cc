You can certainly do this if you want to, but there doesn't seem to be any logical reason. The compiler doesn't complain because this doesn't modify data (which is a pointer) but rather the thing data points to, which is perfectly legal to do with a const pointer. by David Schwartz.