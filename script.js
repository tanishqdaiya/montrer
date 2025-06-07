/* script.js -- Script that runs on each montrer slide
   Author: Tanishq Daiya <tanishqdaiya@yahoo.com>

   This file is a part of montrer (https://github.com/tanishqdaiya/montrer)

   montrer is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   See <https://www.gnu.org/licenses/> for details.*/

/* Listen for keydowns on the left and right arrow keys to click on the links
   that are the previous and next controls in the presentation. */
document.addEventListener("keydown", function (e) {
    switch (e.key) {
    case "ArrowLeft":
        let prev_button = document.getElementById("prev");
        if (!prev_button) console.log("Unable to find element: #prev");
        prev_button.click();
        break;

    case "ArrowRight":
        let next_button = document.getElementById("next");
        if (!next_button) console.log("Unable to find element: #next");
        next_button.click();
        break;
    }
});
