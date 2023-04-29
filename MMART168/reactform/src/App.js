import logo from './logo.svg';
import './App.css';

function App() {
  return (
    <div className="App">
      <form>
        <div className="form-column">
          column
          <div className="form-row" >
            <label>First name</label>
            <input placeholder="John"></input> 
          </div>
          <div className="form-row">
            <label>Last name</label>
            <input placeholder="Smith"></input>
          </div>
        </div>
        <div className="form-column">
          column
          <div className="form-row">
            <label>Email address</label>
            <input placeholder="john@example.com"></input>
          </div>
          <div className="form-row">
            row
          </div>
        </div>
      </form>
    </div>
  );
}

export default App;
