#!/usr/bin/env perl
#OCW v0.91 by Will Grover (wgrover@users.sourceforge.net)
#Released under the GNU General Public License
@in=<>; $|=1;
my @state; ocw(main,1);
sub key_ready {
    my($rin, $nfd);
    vec($rin, fileno(STDIN), 1) = 1;
    return $nfd = select($rin,undef,undef,0); }
sub ocw {
    my $target=shift(@_);
    my $times=shift(@_);
    for(my $time=0;$time<$times;$time++) {
	#changes begin
	if(key_ready) {
	    print "\a";
	    if($times>1) { $input=<STDIN>; }
	    last; }
	#changes end
	my $intarget=0;
	my @addresses; my $address=0;
	foreach (@in) {
	    if(/^armed/) { $armed=1; }
	    elsif(/^negate/) { $negate=1;  }
	    elsif(/^a(\d+)/) { @addresses[$address]=$1; $address++; }
	    elsif(/^$target/) { $intarget=1; }
	    elsif(/^end/) { $intarget=0; }
	    elsif(/\//&&$intarget) { print "\n$_"; }
	    elsif(/^call (\w+) *(\d*)/&&$intarget==1) { 
		if($2) { ocw($1,$2); }
		else { ocw($1,1); } }
	    elsif(/o(\d+)/&&$intarget) {
		print "o$1 ";
		$state[$1/8]=$state[$1/8]|(2**($1%8));
		if($armed==1) {
		    if($negate==1) {
			system './linux', $addresses[$1/8], 255-$state[$1/8]; }
		    else {
			system './linux', $addresses[$1/8], $state[$1/8]; }}} 
	    elsif(/c(\d+)/&&$intarget) {
		print "c$1 ";
		$state[$1/8]=$state[$1/8]&~(2**($1%8));
		if($armed==1) {
		    if($negate==1) {
			system './linux', $addresses[$1/8], 255-$state[$1/8]; }
		    else {
			system './linux', $addresses[$1/8], $state[$1/8]; }}}
	    elsif(/w(\d+)/&&$intarget) {
		print "w$1 "; select(undef,undef,undef,$1/1000); }
	    elsif(/^stop/&&$intarget) { $input = <STDIN>; }
	}
    }
}

