var margin = {top: 30, right: 20, bottom: 140, left: 50},
    width = 600 - margin.left - margin.right,
    height = 470 - margin.top - margin.bottom;
var parseDate = d3.timeParse("%m-%d-%Y %H:%M:%S");

var x = d3.scaleTime().range([0, width]);
var y = d3.scaleLinear().range([height, 0]);

var xAxis = d3.axisBottom().scale(x).ticks(15).tickFormat(d3.timeFormat("%H:%M:%S"));

var yAxis = d3.axisLeft().scale(y).ticks(10);

var valueline = d3.line()
    .x(function(d) { return x(d.timestamp); })
    .y(function(d) { return y(d.cpu); });
var svg = d3.select(".chart")
    .append("svg")
    .attr("width", width + margin.left + margin.right)
    .attr("height", height + margin.top + margin.bottom)
    .append("g")
    .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

var url = "cgi-bin/lab3json.cgi";
var localdata=[] ;
var autoref = false;
var autoRefresh;

d3.json(url,function(data){
	data.forEach(function(d) {
        d.timestamp = parseDate(d.timestamp);
        d.cpu = +d.cpu;
    });
 	localdata = localdata.concat(data);
	x.domain(d3.extent(data, function(d) { return d.timestamp; }));
    y.domain([0, d3.max(data, function(d) { return d.cpu; })]);

    svg.append("path").attr("class", "line")          // Add the valueline path.
        .attr("d", valueline(localdata));

    svg.append("g")                     // Add the X Axis
        .attr("class", "x axis")
        .attr("transform", "translate(0," + height + ")")
        .call(xAxis)
        .selectAll("text")
        .attr("transform","rotate(-45)")
        .style("text-anchor","end");
    svg.append("g")                     // Add the Y Axis
        .attr("class", "y axis")
        .call(yAxis);
});

function refresh() {
    // Get the data again
	d3.json(url,function(data){
		data.forEach(function(d) {
	        d.timestamp = parseDate(d.timestamp);
	        d.cpu = +d.cpu;
	    });
	if(localdata.length > 16) localdata.splice(0,1);
	localdata = localdata.concat(data);

    // Scale the range of the data again
     x.domain(d3.extent(localdata, function(d) { return d.timestamp; }));
     y.domain([0, d3.max(localdata, function(d) { return d.cpu; })]);

    // Select the section we want to apply our changes to
    var svg = d3.select(".chart").transition();
    // Make the changes
    svg.select(".line")   // change the line
        .duration(750)
        .attr("d", valueline(localdata))        ;
    svg.select(".x.axis") // change the x axis
        .duration(750)
        .call(xAxis)
        .selectAll("text")
        .attr("transform","rotate(-45)")
        .style("text-anchor","end");
    svg.select(".y.axis") // change the y axis
        .duration(750)
        .call(yAxis);
    });
}
function toggle(){

	if( autoref ) {
		autoRefresh.stop();
		autoref=false;
		$("a.status").text("pause");
		$("a.status").removeClass("btn-info");
		$("a.status").addClass("btn-default");
		$("a.cpu").addClass("btn-success");
		$("a.cpu").removeClass("btn-warning");

	} else {
		autoRefresh = d3.interval(refresh,3000);
		autoref=true;
		$("a.status").text("running");
		$("a.status").addClass("btn-info");
		$("a.status").removeClass("btn-default");
		$("a.cpu").addClass("btn-warning");
		$("a.cpu").removeClass("btn-success");
	}
}