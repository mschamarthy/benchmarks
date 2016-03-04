#!/usr/bin/perl

=begin comment
============================================================================
 Name        : prerequisites.pl
 Author      : Mohan Shashanka Chamarthy
 CWID		 : A20365258
 Version     : 1.0
 Description : Perl script to check for pre-requisites software installed in
 			   host system & install if not present.
============================================================================
=end comment
=cut

# Check and install gcc
sub gcc_prereq() {
	$var = `which gcc 2>/dev/null`;
	if( !($var =~ /\/gcc/) ){
		print "GCC not present\nAttempting Installation of GCC\n";
		print `sudo yum install gcc`;
	}
}

gcc_prereq();
