var colors = ["#1D507A", "#2F6999", "#66A0D1", "#8FC0E9", "#4682B4"];

var news_data;
d3.json('/send', display_nvd3_graph);

function display_nvd3_graph(data) {
    if (data["status"] == "ok") {
        var temperature_data = [{
            key: 'Température',
            values: data["data"]
        }]

        var first_date = temperature_data[0][0];
        console.log("temperature data: ", temperature_data)

        nv.addGraph(function() {

            var chart = nv.models.lineWithFocusChart()
                .x(function(d) {
                    return d[0]
                })
                .y(function(d) {
                    return d[1]
                })
                .yDomain([-5, 35])
                .height(270)
                .color(colors);

            chart.brushExtent([new Date(first_date), new Date(first_date + 24*3600*1000)]); // 24*3600*1000ms = 1jour

            chart.xAxis
                .showMaxMin(false)
                .tickFormat(function(d) {
                    return d3.time.format('%H:00 (%a)')(new Date(d))
                });

            chart.x2Axis
                .showMaxMin(false)
                .tickFormat(function(d) {
                    return d3.time.format('%a %-d/%-m')(new Date(d))
                });

            chart.yAxis //Chart y-axis settings
                .showMaxMin(false)
                .axisLabel('Température (°c)')
                .tickFormat(d3.format('.00f'));

            chart.y2Axis
                .showMaxMin(false)
                .ticks(false);

            d3.select('#temperature svg')
                .datum(temperature_data)
                .call(chart);

            nv.utils.windowResize(chart.update);

            return chart;
        });
    }
}

console.log("Bonjour mohamed")

 $.ajax({
     url : "/send",
     success: data
 });

console.log("Au revoir")
 function data(result){
    console.log("Affichage des données récupérées: ", result);
}