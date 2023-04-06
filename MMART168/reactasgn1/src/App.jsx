import React from 'react'
import './App.css'

function App() {
  const letters = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'];
  
  const buttons = letters.map( 
    (letter) => {
      return (<button id={letter}>{letter}</button>)
    }
  )
  
  return (
    <div className="App">
      {buttons}
    </div>
  )
}

export default App
