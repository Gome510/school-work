/*Create an external javascript file connected to an HTML File		
Re-create the alien Madlibs 		
Add an additional Question with Prompts and Html IDs		
Add new images with html of spaceships and aliens		
Be sure to add the date and your name as variables		
		
Send a link to your site on codespace or github		*/
function madlib(){
    let date = prompt("Enter today's date")
    let name = prompt("Enter your name")
    let alienName = prompt("Enter an alien name")
    let alienYellOne = prompt("Yell something")
    let alienYellTwo = prompt("Yell something else")
    let adjectiveEverAfter = prompt("Enter an adverb")

    document.getElementById("blankZero").innerHTML = date
    document.getElementById("blankOne").innerHTML = name
    document.getElementById("blankTwo").innerHTML = alienName
    document.getElementById("blankThree").innerHTML = alienYellOne
    document.getElementById("blankFour").innerHTML = alienYellTwo
    document.getElementById("blankFive").innerHTML = adjectiveEverAfter
}



madlib();