import React from "react";
import "./Square.css";

function Square({value}){
    return(
        <button className="square">
            {value}
        </button>
    );
}

export default Square;