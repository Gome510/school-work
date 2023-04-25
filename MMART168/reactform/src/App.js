import logo from './logo.svg';
import './App.css';

function App() {
  return (
    <div className="App">
      <form>
        <row>
          <column className="form-item">
            <label>First Name</label>
            <input placeholder="John"></input>
          </column>
          <column>
            <input placeholder="Smith"></input>
          </column>  
          
          
        </row>
      </form>
    </div>
  );
}

export default App;
