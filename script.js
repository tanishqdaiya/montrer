console.log("Script activated!");

document.addEventListener("keydown", function (e) {
    switch (e.key) {
    case "ArrowLeft":
	let prev_button = document.getElementById("prev");
	console.log(prev_button);
	if (!prev_button) console.log("Unable to find element: #prev");
        prev_button.click();
        break;
	
    case "ArrowRight":
	let next_button = document.getElementById("next");
	console.log(next_button);
	if (!next_button) console.log("Unable to find element: #next");
        next_button.click();
        break;
    }
});
