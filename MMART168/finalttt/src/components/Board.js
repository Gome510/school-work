import React from "react";
import Square from "./Square";
import './Board.css'

function Board(){
    return(
        <div>
            <div className="board-row">
                <Square value={'X'} />
                <Square value={'X'} />
                <Square value={'X'} />
            </div>
            <div className="board-row">
                <Square value={'X'} />
                <Square value={'X'} />
                <Square value={'X'} />
            </div>
            <div className="board-row">
                <Square value={'X'} />
                <Square value={'X'} />
                <Square value={'X'} />
            </div>
        </div>
    );
}

export default Board;