const protocol = "http";
const NodeMCU_IP = "192.168.1.37:5500";
let ONLY_ONE_MODE = false;

$(".loading").click(function () {
    let reqStr = "?p1=%p1%&p2=%p2%&p3=%p3%&p4=%p4%";
    let clicked = $(this);

    // Prepare The Request String
    for (let i = 1; i <= 4; i++) {
        if($(".loading[data-pn=" + i + "]").hasClass('off')) {
            if (clicked.attr('data-pn') == i) {
                reqStr = reqStr.replace("%p" + i + "%", "on");
            } else {
                reqStr = reqStr.replace("%p" + i + "%", "off");
            }
        } else {
            if (clicked.attr('data-pn') == i) {
                reqStr = reqStr.replace("%p" + i + "%", "off");
            } else {
                reqStr = reqStr.replace("%p" + i + "%", "off"); // Make it "off" if you want to swich to "ONLY_ONE_MODE"
            }
        }
    }

    // console.log(reqStr);

    // Send the request
    $.ajax({
        url: protocol + "://" + NodeMCU_IP + reqStr,
        dataType: "text",
        success: msg => {
            // console.log(msg);
            // $(this).toggleClass("off"); // ALL_MODE
            if (clicked.hasClass('off')) { // ONLY_ONE_MODE
                $(".loading").addClass('off');
                $(this).removeClass('off');
            } else {
                $(this).addClass('off');
            }
        },
        error: msg => {
            console.log(msg);
        }
    });

});
