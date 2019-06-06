VCO : MultiOutUGen {
	*ar { |freq = 440, syncin, softsync = 0, pw = 0.5, iphase = 0, analog = 1, calcSin = 1, calcTri = 1, calcSaw = 1, calcSqr = 1|
		if (syncin.isNil) { syncin = 0 };
		^this.multiNew('audio', freq, pw, analog, syncin, softsync, iphase, calcSin, calcTri, calcSaw, calcSqr);
	}

	*sin { |freq = 440, syncin, softsync = 0, iphase = 0, analog = 1|
		var res = this.ar(freq, syncin, softsync, 0.5, iphase, analog, 1, 0, 0, 0);
		if (res[0].isArray) {
			^res.flop[0]
		} {
			^res[0]
		};
	}

	*tri { |freq = 440, syncin, softsync = 0, iphase = 0, analog = 1|
		var res = this.ar(freq, syncin, softsync, 0.5, iphase, analog, 0, 1, 0, 0);
		if (res[0].isArray) {
			^res.flop[1]
		} {
			^res[1]
		};
	}

	*saw { |freq = 440, syncin, softsync = 0, iphase = 0, analog = 1|
		var res = this.ar(freq, syncin, softsync, 0.5, iphase, analog, 0, 0, 1, 0);
		if (res[0].isArray) {
			^res.flop[2]
		} {
			^res[2]
		};
	}

	*sqr { |freq = 440, syncin, softsync = 0, pw = 0.5, iphase = 0, analog = 1|
		var res = this.ar(freq, syncin, softsync, pw, iphase, analog, 0, 0, 0, 1);
		if (res[0].isArray) {
			^res.flop[3]
		} {
			^res[3]
		};
	}

	init { arg ... theInputs;
        inputs = theInputs;
        ^this.initOutputs(4, rate);
    }

	checkInputs {
		/* TODO */
		^this.checkValidInputs;
	}
}
