let buttons = document.querySelectorAll(".fillword-table-container button");

let isPressed = false;
class WordFiller {
    constructor(elem) {
        this.elem = elem;
        // this.oldBackground = elem.style.background;
    }

    handleEvent(event) {
      switch(event.type) {
        case 'mousedown':
          console.log("mousedown");
          this.elem.style.background = "red";
          isPressed = true;
          break;

        case 'mouseover':
          console.log("mouseover")
            if (isPressed) {
                console.log("передвижение");
                this.elem.style.background = "red";
            }
            break;
        
        case 'mouseup':
          console.log("mouseup");
          isPressed = false;
          break;
      }
    }
}

//button.addEventListener("mouseup", (event) => )
buttons.forEach(button => button.addEventListener("mousedown", new WordFiller(button)));
buttons.forEach(button => button.addEventListener("mouseup", new WordFiller(button)));
buttons.forEach(button => button.addEventListener("mouseover", new WordFiller(button)));